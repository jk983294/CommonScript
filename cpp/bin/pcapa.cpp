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
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

/**
 * g++ pcap.cpp -lpcap
 * ./pcap -f 20190906_2.pcap | egrep 'InputOrder|time' | less
 * ./pcap -f 20190906_2.pcap | egrep '^time' | cut2 | stats
 *
 * echo
 * pcap -f /tmp/echo.pcap -m 10.18.0.192:30057 -d 10.18.0.191 -c ""
 */

/**
 * in_src_host --> middle_endpoint --> out_dest_endpoint
 */
string middle_endpoint{"172.218.10.12:60050"};
std::unordered_set<string> middle_endpoints;
std::unordered_map<string, string> in2out;
std::unordered_map<string, string> out2in;
string out_dest_host;
string content, map_content;
int out_dest_port = 0;
int input_packet_length = 0;
int output_packet_length = 0;
int input_packet_offset = -1;
int output_packet_offset = -1;
int offset_match_length = -1;
bool offset_match_mode = false;

std::string getIp(u_int32_t);
void handle_packet(const u_char *payload, size_t data_len);
inline double timeval2double(const timeval &ts);
bool can_find_content(const u_char *src, size_t src_len);
void print_content(const u_char *src, size_t src_len);
string extract_offset_content(const u_char *src, int offset, int len);
bool match_input_len(int pkt_len) { return input_packet_length == 0 || input_packet_length == pkt_len; }
bool match_output_len(int pkt_len) { return output_packet_length == 0 || output_packet_length == pkt_len; }
std::vector<string> split(const string &input, char delimit);

struct Item {
    double timestamp;
    int frame_index;
    string extra_match_tick;

    Item(double timestamp_, int index_) : timestamp{timestamp_}, frame_index{index_} {}
    Item(double timestamp_, int index_, const string &extra_match_tick_)
        : timestamp{timestamp_}, frame_index{index_}, extra_match_tick{extra_match_tick_} {}
};

struct Stats {
    std::unordered_map<string, std::list<Item>> matchContent2ins;

    void add_in(const string &in_matched_content, const Item &item) {
        if (item.extra_match_tick.empty()) {
            matchContent2ins[in_matched_content].push_back(item);
        } else {
            std::list<Item> &ins = matchContent2ins[in_matched_content];
            if (!ins.empty()) {  // idea is to keep first tick since there are multiply md source
                if (ins.front().extra_match_tick != item.extra_match_tick) {
                    ins.clear();
                    matchContent2ins[in_matched_content].push_back(item);
                }
            } else {
                matchContent2ins[in_matched_content].push_back(item);
            }
        }
    }
    void add_out(const string &out_matched_content, const Item &out) {
        if (out2in.count(out_matched_content) == 0) return;

        std::list<Item> &ins = matchContent2ins[out2in[out_matched_content]];
        if (ins.empty()) return;

        Item &in = ins.back();
        cout << "time " << (out.timestamp - in.timestamp) << " from " << in.frame_index << " to " << out.frame_index
             << endl;

        ins.clear();
    }
};

void help() {
    std::cout << "Program options:" << std::endl;
    std::cout << "  -h                                    list help" << std::endl;
    std::cout << "  -f                                    pcap file" << std::endl;
    std::cout << "  -m arg (=172.218.10.12:60050)         middle endpoint, multi source separated by comma ','"
              << std::endl;
    std::cout << "  -d arg (=)                            out dest host" << std::endl;
    std::cout << "  -p arg (=0)                           out dest port (0 means it will get from first matched "
                 "content's endpoint)"
              << std::endl;
    std::cout << "  -c arg (=)                            content to lookup (set it to '' to ignore content match)"
              << std::endl;
    std::cout << "  -x arg (=0)                           input packet length" << std::endl;
    std::cout << "  -y arg (=0)                           output packet length" << std::endl;
    std::cout << "  -X arg (=-1)                          input packet offset to match" << std::endl;
    std::cout << "  -Y arg (=-1)                          output packet offset to match" << std::endl;
    std::cout << "  -Z arg (=-1)                          content match length regard to offset" << std::endl;
    std::cout << "  -M arg (=)                            content mapping, format in1:out1,in2:out2" << std::endl;
    std::cout << "  -N                                    time precision, use ns instead of us" << std::endl;
    std::cout << "  -P                                    display hex content" << std::endl;
    std::cout << "example: ./pcap -f file | egrep '^time' | cut2 | stats" << std::endl;
}

int frame_count = 0;
string out_dest_endpoint;  // port is unknown to us at first
bool first_order_in = false;
bool out_port_found = false;
Stats stats;
string src_ip;
string src_endpoint;
string dest_ip;
int dest_port;
string dest_endpoint;
double ts;
bool isUs{true};
bool isPrintHex{false};

int main(int argc, char *argv[]) {
    int opt;
    string file_path;
    while ((opt = getopt(argc, argv, "hNPm:d:c:f:p:x:y:X:Y:Z:M:")) != -1) {
        switch (opt) {
            case 'p':
                out_dest_port = std::stoi(optarg);
                break;
            case 'N':
                isUs = false;
                break;
            case 'P':
                isPrintHex = true;
                break;
            case 'x':
                input_packet_length = std::stoi(optarg);
                break;
            case 'y':
                output_packet_length = std::stoi(optarg);
                break;
            case 'X':
                input_packet_offset = std::stoi(optarg);
                break;
            case 'Y':
                output_packet_offset = std::stoi(optarg);
                break;
            case 'Z':
                offset_match_length = std::stoi(optarg);
                break;
            case 'm':
                middle_endpoint = optarg;
                break;
            case 'd':
                out_dest_host = optarg;
                break;
            case 'c':
                content = optarg;
                break;
            case 'M':
                map_content = optarg;
                break;
            case 'f':
                file_path = optarg;
                break;
            case 'h':
                help();
                return 0;
            default:
                abort();
        }
    }

    vector<string> strs = split(middle_endpoint, ',');
    for (auto &str : strs) {
        cout << "install middle_endpoint " << str << endl;
        middle_endpoints.insert(str);
    }

    if (!content.empty()) {
        in2out[content] = content;
        out2in[content] = content;
        cout << "install mapping content from -c option " << content << " <-> " << content << endl;
    }
    if (!map_content.empty()) {
        vector<string> mappings = split(map_content, ',');
        for (auto &mapping : mappings) {
            vector<string> lets = split(mapping, ':');
            if (lets.size() == 2 && !lets[0].empty() && !lets[1].empty() && in2out.count(lets[0]) == 0 &&
                out2in.count(lets[1]) == 0) {
                in2out[lets[0]] = lets[1];
                out2in[lets[1]] = lets[0];
                cout << "install mapping content " << lets[0] << " <-> " << lets[1] << endl;
            } else {
                cout << "ignore mapping content: " << mapping << endl;
            }
        }
    }

    if (input_packet_offset >= 0 && output_packet_offset >= 0 && offset_match_length > 0) {
        offset_match_mode = true;
        cout << "enable offset match mode input_packet_offset: " << input_packet_offset
             << " output_packet_offset: " << output_packet_offset << " offset_match_length: " << offset_match_length
             << endl;
    }

    out_dest_endpoint = out_dest_host + ":";  // port is unknown to us at first
    if (out_dest_port > 0) {
        first_order_in = true;
        out_port_found = true;
        out_dest_endpoint += std::to_string(out_dest_port);
    }

    char err_buf[PCAP_ERRBUF_SIZE];
    pcap_t *handle = nullptr;
    if (isUs)
        handle = pcap_open_offline(file_path.c_str(), err_buf);
    else
        handle = pcap_open_offline_with_tstamp_precision(file_path.c_str(), PCAP_TSTAMP_PRECISION_NANO, err_buf);
    if (handle == nullptr) {
        std::cerr << "pcap_open: " << err_buf << std::endl;
        return 1;
    }

    cout << setprecision(19);
    pcap_pkthdr header{};
    const u_char *p;

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
        ts = timeval2double(tv);
        if (ip->protocol == IPPROTO_UDP) {
            const udphdr *udp = reinterpret_cast<const udphdr *>(p + sizeof(ether_header) + ip->ihl * 4);

            src_ip = getIp(ip->saddr);
            src_endpoint = src_ip + ":" + std::to_string(ntohs(udp->source));
            dest_ip = getIp(ip->daddr);
            dest_port = ntohs(udp->dest);
            dest_endpoint = dest_ip + ":" + std::to_string(dest_port);

            ssize_t data_len = ntohs(udp->len) - 8;
            if (data_len == 0) continue;

            const u_char *udp_payload = &p[sizeof(ether_header) + ip->ihl * 4 + sizeof(udphdr)];
            cout << "frame " << frame_count << " " << ts << " udp_header " << src_ip << ":" << ntohs(udp->source)
                 << " --> " << dest_ip << ":" << dest_port << " udp_data_len: " << data_len;

            handle_packet(udp_payload, data_len);
        } else if (ip->protocol == IPPROTO_TCP) {
            const auto *tcp_header = reinterpret_cast<const tcphdr *>(p + sizeof(ether_header) + ip->ihl * 4);

            src_ip = getIp(ip->saddr);
            src_endpoint = src_ip + ":" + std::to_string(ntohs(tcp_header->source));
            dest_ip = getIp(ip->daddr);
            dest_port = ntohs(tcp_header->dest);
            dest_endpoint = dest_ip + ":" + std::to_string(dest_port);

            uint64_t seq = ntohl(tcp_header->seq);
            uint16_t data_offset = tcp_header->doff;  // th_off
            uint16_t ip_total_len = ntohs(ip->tot_len);
            uint64_t tcp_data_len = ip_total_len - (ip->ihl + data_offset) * 4;
            const u_char *tcp_payload = &p[sizeof(ether_header) + ip->ihl * 4 + data_offset * 4];

            if (tcp_data_len == 0) continue;

            cout << "frame " << frame_count << " " << ts << " tcp_header " << src_ip << ":" << ntohs(tcp_header->source)
                 << " --> " << dest_ip << ":" << dest_port << " seq: " << seq << " ack: " << ntohl(tcp_header->ack_seq)
                 << " tcp_data_len: " << tcp_data_len;

            handle_packet(tcp_payload, tcp_data_len);
        }
    }
    return 0;
}

void handle_packet(const u_char *payload, size_t data_len) {
    string matched = "not_in_match_mode";
    string extra_tick_info;
    if (first_order_in && !out_port_found && match_output_len(data_len) && dest_ip == out_dest_host &&
        can_find_content(payload, data_len)) {
        out_dest_endpoint.append(to_string(dest_port));
        cout << " found out port: " << dest_port << " out_dest_endpoint update to " << out_dest_endpoint;
        out_port_found = true;
    }

    if (middle_endpoints.count(dest_endpoint) > 0 && match_input_len(data_len) && can_find_content(payload, data_len)) {
        if (offset_match_mode) {
            matched = extract_offset_content(payload, input_packet_offset, offset_match_length);
            if (in2out.count(matched) == 0) {
                cout << endl;
                return;
            }

            // TODO below is hack for CFFEX market data, snapshot tick
            uint32_t tickMill = ntohl(*reinterpret_cast<const uint32_t *>(payload + 64));
            extra_tick_info = extract_offset_content(payload, 55, 8) + "_" + std::to_string(tickMill);
            cout << " matched: " << matched << " tick: " << extra_tick_info;
        }
        cout << " InputOrder In" << endl;
        stats.add_in(matched, Item{ts, frame_count, extra_tick_info});
        print_content(payload, data_len);

        if (!first_order_in && !out_port_found) {
            first_order_in = true;
        }
    } else if (dest_endpoint == out_dest_endpoint && match_output_len(data_len) &&
               can_find_content(payload, data_len)) {
        if (offset_match_mode) {
            matched = extract_offset_content(payload, output_packet_offset, offset_match_length);
            if (out2in.count(matched) == 0) {
                cout << endl;
                return;
            }
            cout << " matched: " << matched;
        }
        cout << " InputOrder Out" << endl;
        stats.add_out(matched, Item{ts, frame_count});
        print_content(payload, data_len);
    } else {
        cout << endl;
    }
}

std::string getIp(u_int32_t ip) {
    char buffer[17];
    std::snprintf(buffer, sizeof buffer, "%u.%u.%u.%u", static_cast<uint8_t>(ip & 0xFF),
                  static_cast<uint8_t>((ip >> 8) & 0xFF), static_cast<uint8_t>((ip >> 16) & 0xFF),
                  static_cast<uint8_t>((ip >> 24) & 0xFF));
    return string(buffer);
}

bool can_find_content(const u_char *src, size_t src_len) {
    size_t target_len = content.size();
    if (target_len == 0) return true;  // ignore content match
    if (src_len < target_len) return false;

    for (size_t i = 0; i < src_len - target_len; ++i) {
        if (memcmp(content.c_str(), src + i, target_len) == 0) return true;
    }
    return false;
}

void print_content(const u_char *src, size_t src_len) {
    if (!isPrintHex) return;
    cout << "hex:  " << std::hex;
    for (size_t i = 0; i < src_len; ++i) {
        uint32_t data = src[i];
        cout << setfill('0') << setw(2) << data;
    }
    cout << std::dec << std::endl;

    cout << "char: " << std::hex;
    for (size_t i = 0; i < src_len; ++i) {
        uint32_t data = src[i];
        if ((data >= 48 && data <= 57) || (data >= 65 && data <= 90) || (data >= 97 && data <= 122)) {
            cout << " " << char(data - 0);
        } else {
            cout << "_-";
        }
    }
    cout << std::dec << std::endl;
}

string extract_offset_content(const u_char *src, int offset, int len) {
    char match_content[256];
    memset(match_content, 0, sizeof(match_content));
    memcpy(match_content, src + offset, len);
    return std::string(match_content);
}

inline double timeval2double(const timeval &ts) {
    if (isUs)
        return static_cast<double>(ts.tv_sec) + (static_cast<double>(ts.tv_usec) / 1000000.0);
    else
        return static_cast<double>(ts.tv_sec) + (static_cast<double>(ts.tv_usec) / 1000000000.0);
}

std::vector<string> split(const string &input, char delimit) {
    std::vector<string> strings;
    istringstream f(input);
    string s;
    while (getline(f, s, delimit)) {
        strings.push_back(s);
    }
    return strings;
}
