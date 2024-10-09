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
 * g++ -std=c++17 ipc_writer_first.cpp -lrt
 */

constexpr size_t MAX_LEN = 101; // extra 1 in case allocation fail
constexpr size_t REAL_LEN = 80;

struct MyValue {
    int idx;
    int value;
};

struct MyData {
    MyValue value;
    std::atomic_uint64_t writer_idx = 0;

    void write_data(const MyValue& d) {
        writer_idx += 1;
        value = d;
        writer_idx += 1;
    }
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

    void write(int ukey, MyValue& data) {
        auto& d_ = m_pData[ukey2idx(ukey)];
        d_.write_data(data);
    }

    void read(int ukey, MyValue& data) {
        auto& d_ = m_pData[ukey2idx(ukey)];

        while (true) {
            uint64_t old = d_.writer_idx.load(std::memory_order_acquire);
            if (old % 2 == 1) continue; // writer is writing
            data = d_.value;
            uint64_t new_ = d_.writer_idx.load(std::memory_order_acquire);
            if (old == new_) return;
        }
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
