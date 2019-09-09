#include <net/ethernet.h>
#include <net/if.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <netinet/udp.h>
#include <pcap/pcap.h>
#include <sys/time.h>
#include <unistd.h>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <list>
#include <string>

using namespace std;

/**
 * g++ pcap.cpp -lpcap
 * ./pcap my.pcap
 * ./pcap 20190906_2.pcap | egrep 'InputOrder|time' | less
 * ./pcap 20190906_2.pcap | egrep '^time' | cut2 | stats
 */

const char *const instrument = "TF1909";

std::string getIp(u_int32_t);

inline double timeval2double(const timeval &ts) {
    return static_cast<double>(ts.tv_sec) + (static_cast<double>(ts.tv_usec) / 1000000.0);
}

bool can_find_ins(const u_char *src, size_t src_len);

struct Item {
    double timestamp;
    uint64_t seq;
    int frame_index;

    Item(double timestamp_, uint64_t seq_, int index_) : timestamp{timestamp_}, seq{seq_}, frame_index{index_} {}
};

struct Stats {
    std::list<Item> ins;

    void add_in(Item item) { ins.push_back(item); }
    void add_out(Item out) {
        if (ins.empty()) return;

        Item &in = ins.back();
        cout << "time " << (out.timestamp - in.timestamp) << " from " << in.frame_index << " to " << out.frame_index
             << endl;

        ins.clear();
    }
};

int main(int argc, char *argv[]) {
    /**
     * in_src_host --> order_endpoint --> out_dest_endpoint
     */
    string in_src_host{"10.18.0.191"};
    string order_endpoint{"10.18.0.166:9000"};
    string out_dest_host{"117.131.114.103"};
    string out_dest_endpoint = out_dest_host + ":";  // port is unknown to us at first
    bool first_order_in = false;
    bool out_port_found = false;

    char err_buf[PCAP_ERRBUF_SIZE];
    pcap_t *handle = pcap_open_offline(argv[1], err_buf);
    if (handle == nullptr) {
        std::cerr << "pcap_open: " << err_buf << std::endl;
        return 1;
    }

    Stats stats;

    cout << setprecision(19);
    pcap_pkthdr header{};
    const u_char *p;
    int frame_count = 0;
    while ((p = pcap_next(handle, &header))) {
        frame_count++;
        if (header.len != header.caplen) {
            continue;
        }
        auto eth = reinterpret_cast<const ether_header *>(p);
        if (ntohs(eth->ether_type) != ETHERTYPE_IP) {
            continue;
        }
        auto ip = reinterpret_cast<const iphdr *>(p + sizeof(ether_header));
        if (ip->version != 4) {
            continue;
        }

        timeval tv = header.ts;
        if (ip->protocol == IPPROTO_UDP) {
            // ignore udp
        } else if (ip->protocol == IPPROTO_TCP) {
            const auto *tcp_header = reinterpret_cast<const tcphdr *>(p + sizeof(ether_header) + ip->ihl * 4);

            string src_ip = getIp(ip->saddr);
            string src_endpoint = src_ip + ":" + std::to_string(ntohs(tcp_header->source));
            string dest_ip = getIp(ip->daddr);
            string dest_endpoint = dest_ip + ":" + std::to_string(ntohs(tcp_header->dest));
            double ts = timeval2double(tv);
            uint64_t seq = ntohl(tcp_header->seq);
            uint16_t data_offset = tcp_header->th_off;
            uint16_t ip_total_len = ntohs(ip->tot_len);
            uint64_t tcp_data_len = ip_total_len - (ip->ihl + data_offset) * 4;
            const u_char *tcp_payload = &p[sizeof(ether_header) + ip->ihl * 4 + data_offset * 4];

            cout << "frame " << frame_count << " " << ts << " tcp_header " << src_ip << ":" << ntohs(tcp_header->source)
                 << " --> " << dest_ip << ":" << ntohs(tcp_header->dest) << " seq: " << seq
                 << " ack: " << ntohl(tcp_header->ack_seq) << " tcp_data_len: " << tcp_data_len;

            if (first_order_in && !out_port_found && can_find_ins(tcp_payload, tcp_data_len)) {
                out_dest_endpoint.append(to_string(ntohs(tcp_header->dest)));
                cout << " found out port: " << ntohs(tcp_header->dest) << " out_dest_endpoint update to "
                     << out_dest_endpoint;
                out_port_found = true;
            }

            if (dest_endpoint == order_endpoint && can_find_ins(tcp_payload, tcp_data_len)) {
                cout << " InputOrder In" << endl;
                stats.add_in(Item{ts, seq, frame_count});

                if (!first_order_in && !out_port_found) {
                    first_order_in = true;
                }
            } else if (dest_endpoint == out_dest_endpoint && can_find_ins(tcp_payload, tcp_data_len)) {
                cout << " InputOrder Out" << endl;
                stats.add_out(Item{ts, seq, frame_count});
            } else {
                cout << endl;
                continue;
            }
        }
    }
    return 0;
}

std::string getIp(u_int32_t ip) {
    char buffer[17];
    std::snprintf(buffer, sizeof buffer, "%u.%u.%u.%u", static_cast<uint8_t>(ip & 0xFF),
                  static_cast<uint8_t>((ip >> 8) & 0xFF), static_cast<uint8_t>((ip >> 16) & 0xFF),
                  static_cast<uint8_t>((ip >> 24) & 0xFF));
    return string(buffer);
}

bool can_find_ins(const u_char *src, size_t src_len) {
    size_t target_len = strlen(instrument);
    if (src_len < target_len) return false;

    for (size_t i = 0; i < src_len - target_len; ++i) {
        if (memcmp(instrument, src + i, target_len) == 0) return true;
    }
    return false;
}
