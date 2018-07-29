#include <net/ethernet.h>
#include <net/if.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <netinet/udp.h>
#include <pcap/pcap.h>
#include <unistd.h>
#include <cstring>
#include <iostream>
#include <string>

using namespace std;

/**
 * g++ pcap.cpp -lpcap
 * ./pcap my.pcap
 */

std::string timeval2string(const struct timeval &tv);
std::string getIp(u_int32_t);

int main(int argc, char *argv[]) {
    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t *handle = pcap_open_offline(argv[1], errbuf);
    if (handle == nullptr) {
        std::cerr << "pcap_open: " << errbuf << std::endl;
        return 1;
    }

    pcap_pkthdr header;
    const u_char *p;
    while ((p = pcap_next(handle, &header))) {
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
            const udphdr *udp = reinterpret_cast<const udphdr *>(p + sizeof(ether_header) + ip->ihl * 4);
            ssize_t len = ntohs(udp->len) - 8;
            // const u_char *udpPayload = &p[sizeof(ether_header) + ip->ihl * 4 + sizeof(udphdr)];
            cout << timeval2string(tv) << " udp " << getIp(ip->saddr) << ":" << ntohs(udp->source) << " --> "
                 << getIp(ip->daddr) << ":" << ntohs(udp->dest) << " len: " << len << endl;
        } else if (ip->protocol == IPPROTO_TCP) {
            const tcphdr *tcp = reinterpret_cast<const tcphdr *>(p + sizeof(ether_header) + ip->ihl * 4);
            // const u_char *tcpPayload = &p[sizeof(ether_header) + ip->ihl * 4 + sizeof(tcphdr)];
            cout << timeval2string(tv) << " tcp " << getIp(ip->saddr) << ":" << ntohs(tcp->source) << " --> "
                 << getIp(ip->daddr) << ":" << ntohs(tcp->dest) << " seq: " << ntohl(tcp->seq)
                 << " ack: " << ntohl(tcp->ack_seq) << endl;
        }
    }
    return 0;
}

std::string timeval2string(const struct timeval &tv) {
    struct tm tm;
    localtime_r(&tv.tv_sec, &tm);
    char buffer[24];
    std::snprintf(buffer, sizeof buffer, "%4u-%02u-%02u %02u:%02u:%02u.%03u", tm.tm_year + 1900, tm.tm_mon + 1,
                  tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec, static_cast<uint16_t>(tv.tv_usec / 1000));
    return string(buffer);
}

std::string getIp(u_int32_t ip) {
    char buffer[17];
    std::snprintf(buffer, sizeof buffer, "%u.%u.%u.%u", static_cast<uint8_t>(ip & 0xFF),
                  static_cast<uint8_t>((ip >> 8) & 0xFF), static_cast<uint8_t>((ip >> 16) & 0xFF),
                  static_cast<uint8_t>((ip >> 24) & 0xFF));
    return string(buffer);
}
