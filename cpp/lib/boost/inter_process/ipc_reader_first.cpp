#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/sync/interprocess_sharable_mutex.hpp>
#include <boost/interprocess/sync/sharable_lock.hpp>
#include <boost/interprocess/sync/scoped_lock.hpp>
#include <iostream>
#include <cstdlib>
#include <atomic>
#include <chrono>
#include <unordered_map>
#include <getopt.h>

namespace ipc = boost::interprocess;

/**
 * g++ -std=c++17 ipc_reader_first.cpp -lrt
 */

constexpr size_t MAX_LEN = 101; // extra 1 in case allocation fail
constexpr size_t REAL_LEN = 100;
constexpr int RING_BUF_LEN = 10;

struct MyValue {
    int idx;
    int value;
};

struct MyData {
    using mutex_t = ipc::interprocess_sharable_mutex;
    MyValue value[RING_BUF_LEN];
    mutex_t mtx[RING_BUF_LEN];
    std::atomic_int reader_idx = 0;
    std::atomic_int writer_idx = 0;

    auto& get_reader_mutex() { return mtx[reader_idx]; }
    auto& get_writer_mutex() { return mtx[writer_idx]; }
    auto& get_reader_data() { return value[reader_idx]; }
    void write_data(const MyValue& d) { value[writer_idx] = d; }
};

struct ShmManager {
    bool m_writer{false};
    std::string m_shm_name;
    std::string m_all_ukey_name{"all_ukeys"};
    std::string m_all_ukey_data_name{"ukey2data"};
    ipc::managed_shared_memory m_shm;
    int32_t* m_all_ukeys{nullptr};
    MyData* m_pData{nullptr};
    std::unordered_map<int32_t, size_t> m_ukey2idx;

    ShmManager(bool writer_, std::string shm_name): m_writer{writer_}, m_shm_name{shm_name} {
        if (writer_) open_create();
        else open_read();
    }

    bool write(int ukey, MyValue& data) {
        auto& d_ = m_pData[ukey2idx(ukey)];
        int i = 0;
        bool ret = false;
        for (; i < RING_BUF_LEN; ++i) {
            ipc::scoped_lock lock(d_.get_writer_mutex(), ipc::defer_lock);
            if (d_.writer_idx.load() != d_.reader_idx.load() && lock.try_lock()) {
                d_.write_data(data);
                lock.unlock();

                d_.reader_idx = d_.writer_idx.load();
                d_.writer_idx = (d_.writer_idx.load() + 1) % RING_BUF_LEN;
                ret = true;
                break;
            } else {
                d_.writer_idx = (d_.writer_idx.load() + 1) % RING_BUF_LEN;
            }
        }

        if (!ret && i >= RING_BUF_LEN) {
            printf("Error, no slot to write %d\n", ukey);
        }
        return ret;
    }

    bool read(int ukey, MyValue& data) {
        auto& d_ = m_pData[ukey2idx(ukey)];

        ipc::sharable_lock lock(d_.get_reader_mutex(), ipc::defer_lock);

        // if (lock.try_lock_for(std::chrono::microseconds(1))) {
        if (lock.try_lock()) {
            data = d_.get_reader_data();
            return true;
        }
        return false;
    }

private:
    size_t ukey2idx(int32_t ukey) { return m_ukey2idx[ukey]; }
    void open_create() {
        ipc::shared_memory_object::remove(m_shm_name.c_str());
        m_shm = ipc::managed_shared_memory(ipc::create_only, m_shm_name.c_str(),
                                           MAX_LEN * (sizeof(MyData) + sizeof(int32_t)),
                                           nullptr, ipc::permissions(0666));
        printf("%s is created\n", m_shm_name.c_str());

        create_ukey2idx();
        create_ukey2data();
    }
    void open_read() {
        try {
            m_shm = ipc::managed_shared_memory(ipc::open_only, m_shm_name.c_str());
            printf("%s is opened\n", m_shm_name.c_str());

            for (auto itr = m_shm.named_begin(); itr != m_shm.named_end(); ++itr) {
                printf("shm found: %s\n", itr->name());
            }
            size_t cnt;
            std::tie(m_all_ukeys, cnt) = m_shm.find<int32_t>(m_all_ukey_name.c_str());

            if (!m_all_ukeys) {
                printf("cannot find %s\n", m_all_ukey_name.c_str());
                exit(1);
            } else if (cnt != REAL_LEN) {
                printf("wrong size for %s\n", m_all_ukey_name.c_str());
                exit(1);
            }

            build_ukey2idx();

            cnt = 0;
            std::tie(m_pData, cnt) = m_shm.find<MyData>(m_all_ukey_data_name.c_str());

            if (!m_pData) {
                printf("cannot find %s\n", m_all_ukey_data_name.c_str());
                exit(1);
            } else if (cnt != REAL_LEN) {
                printf("wrong size for %s\n", m_all_ukey_data_name.c_str());
                exit(1);
            }
        } catch (std::exception& e) {
            printf("error on open %s : %s\n", m_shm_name.c_str(), e.what());
            exit(1);
        }
    }

    void create_ukey2data() {
        m_pData = m_shm.construct<MyData>(m_all_ukey_data_name.c_str())[REAL_LEN]();
        if (!m_pData) {
            printf("cannot create %s\n", m_all_ukey_data_name.c_str());
            exit(1);
        }
    }

    void create_ukey2idx() {
        m_all_ukeys = m_shm.construct<int32_t>(m_all_ukey_name.c_str())[REAL_LEN](0); // init to 0
        if (!m_all_ukeys) {
            printf("cannot create %s\n", m_all_ukey_name.c_str());
            exit(1);
        }

        for (size_t i = 0; i < REAL_LEN; ++i) {
            m_all_ukeys[i] = 10600000 + i;
        }

        build_ukey2idx();
    }

    void build_ukey2idx() {
        for (size_t i = 0; i < REAL_LEN; ++i) {
            m_ukey2idx.emplace(m_all_ukeys[i], i);
        }
    }
};

int main(int argc, char** argv) {
    std::string shm_name = "shm_test";
    bool writer = false;
    int opt;
    while ((opt = getopt(argc, argv, "w")) != -1) {
        switch (opt) {
            case 'w':
                writer = true;
                break;
            default:
                abort();
        }
    }
    ShmManager* mgr = new ShmManager(writer, shm_name);
    int ukey = 10600001;
    int idx = 0;
    MyValue data;
    if (writer) {
        while (true) {
            data.idx = idx++;
            data.value = idx;
            mgr->write(ukey, data);
            printf("write %d %d\n", ukey, idx);
            sleep(1);
        }
    } else {
        while (true) {
            mgr->read(ukey, data);
            printf("read %d %d\n", ukey, data.value);
            sleep(1);
        }
    }
    return 0;
}
