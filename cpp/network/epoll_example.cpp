#include <sys/epoll.h>
#include <unistd.h>
#include <cstring>
#include <iostream>

using namespace std;

int main() {
    const int MAX_EVENTS = 5;
    const int BUFFER_SIZE = 10;
    struct epoll_event event, events[MAX_EVENTS];
    int epollFd = epoll_create1(0);

    if (epollFd == -1) {
        cerr << "failed to create epoll file descriptor" << endl;
        return 1;
    }

    event.events = EPOLLIN;
    event.data.fd = 0;

    /**
     * unlike poll, epoll copy fd exactly one time from user mode to kernel mode
     */
    if (epoll_ctl(epollFd, EPOLL_CTL_ADD, 0, &event)) {
        cerr << "failed to add file descriptor to epoll" << endl;
        close(epollFd);
        return 1;
    }

    char buffer[BUFFER_SIZE + 1];
    bool running = true;
    while (running) {
        cout << "polling for input..." << endl;
        int eventCount = epoll_wait(epollFd, events, MAX_EVENTS, 30000);  // 30s timeout

        /**
         * when input is "01234567890123456789\n"
         * if Level Triggered, you will receive 3 times IO ready signal, "0123456789", "0123456789", "\n"
         * if Edge Triggered, only 1 time IO ready signal received, if no new input, no signal will be triggered
         */
        for (int i = 0; i < eventCount; ++i) {
            long bytesRead = read(events[i].data.fd, buffer, BUFFER_SIZE);
            buffer[bytesRead] = '\0';
            cout << bytesRead << " read: " << buffer << endl;

            if (!strncmp(buffer, "stop\n", 5)) {
                running = false;
            }
        }
    }

    if (close(epollFd)) {
        cerr << "failed to close epoll file descriptor" << endl;
        return 1;
    }
    return 0;
}
