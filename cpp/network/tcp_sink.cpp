#include <arpa/inet.h>
#include <netdb.h>
#include <sys/socket.h>
#include <unistd.h>
#include <cstring>
#include <iostream>
#include <string>

using namespace std;

/**
 * ./tcp_sink -p 28023
 */

void help() {
    std::cout << "Program options:" << std::endl;
    std::cout << "  -h                                    list help" << std::endl;
    std::cout << "  -p                                    port" << std::endl;
}

int main(int argc, char *argv[]) {
    size_t size = 1024;
    string port{"28023"};

    int opt;
    while ((opt = getopt(argc, argv, "hp:")) != -1) {
        switch (opt) {
            case 'p':
                port = std::string(optarg);
                break;
            case 'h':
                help();
            default:
                abort();
        }
    }

    struct addrinfo *res;
    int sockfd, new_fd;

    struct addrinfo hints;
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;  // use IPv4 or IPv6, whichever
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;  // fill in my IP for me

    int ret = getaddrinfo("0.0.0.0", port.c_str(), &hints, &res);
    if (ret != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(ret));
        return 1;
    }

    if ((sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol)) == -1) {
        perror("socket");
        return 1;
    }

    int yes = 1;
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
        perror("setsockopt");
        return 1;
    }

    if (bind(sockfd, res->ai_addr, res->ai_addrlen) == -1) {
        perror("bind");
        return 1;
    }

    if (listen(sockfd, 1) == -1) {
        perror("listen");
        return 1;
    }
    cout << "listen on 0:" << port << endl;

    struct sockaddr_in client_addr;
    int addr_size = sizeof(client_addr);

    char *buf = new char[size];
    while (true) {
        if ((new_fd = accept(sockfd, (struct sockaddr *)&client_addr, (socklen_t *)&addr_size)) == -1) {
            perror("accept");
            return 1;
        }
        string clientIp = inet_ntoa(client_addr.sin_addr);
        string clientEndpoint_ = clientIp;
        clientEndpoint_ += ':';
        clientEndpoint_ += std::to_string(ntohs(client_addr.sin_port));
        cout << "serve " << clientEndpoint_ << endl;

        int len = 0;
        while (true) {
            len = read(new_fd, buf, size);
            if (len == 0) {
                cout << "client leave" << endl;
                break;
            } else if (len < 0) {
                if ((EINTR == errno) || (EAGAIN == errno)) {
                    continue;
                } else {
                    perror("end read");
                    break;
                }
            } else {
                cout << "recv " << len << endl;
            }
        }
    }
}
