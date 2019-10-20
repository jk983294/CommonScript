#define _GNU_SOURCE
#include <assert.h>
#include <dlfcn.h>
#include <fcntl.h>
#include <net/if.h>
#include <netinet/ether.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <netinet/udp.h>
#include <poll.h>
#include <sched.h>
#include <signal.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/epoll.h>
#include <sys/ioctl.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

/**
 * LD_PRELOAD=./libmynet.so ./tcp_sink
 */

bool __override_initialized = false;

int (*__libc_socket)(int, int, int);
int (*__libc_close)(int);
int (*__libc_bind)(int, const struct sockaddr *, socklen_t);
int (*__libc_listen)(int, int);
int (*__libc_accept)(int, struct sockaddr *, socklen_t *);
int (*__libc_accept4)(int, struct sockaddr *, socklen_t *, int);
int (*__libc_connect)(int, const struct sockaddr *, socklen_t);
int (*__libc_shutdown)(int, int);
int (*__libc_fcntl)(int, int, ...);
int (*__libc_ioctl)(int d, int request, void *argp);
int (*__libc_getsockname)(int, struct sockaddr *, socklen_t *);
int (*__libc_getpeername)(int, struct sockaddr *, socklen_t *);
int (*__libc_getsockopt)(int, int, int, void *, socklen_t *);
int (*__libc_setsockopt)(int, int, int, const void *, socklen_t);
ssize_t (*__libc_recv)(int, void *, size_t, int);
ssize_t (*__libc_recvfrom)(int, void *, size_t, int, struct sockaddr *, socklen_t *);
ssize_t (*__libc_recvmsg)(int, struct msghdr *, int);
ssize_t (*__libc_send)(int, const void *, size_t, int);
ssize_t (*__libc_sendto)(int, const void *, size_t, int, const struct sockaddr *, socklen_t);
ssize_t (*__libc_sendmsg)(int, const struct msghdr *, int);
ssize_t (*__libc_read)(int, void *, size_t);
ssize_t (*__libc_readv)(int, const struct iovec *iov, int iovcnt);
ssize_t (*__libc_write)(int, const void *, size_t);
ssize_t (*__libc_writev)(int, const struct iovec *iov, int iovcnt);
int (*__libc_select)(int, fd_set *, fd_set *, fd_set *, struct timeval *);
int (*__libc_pselect)(int, fd_set *, fd_set *, fd_set *, const struct timespec *, const sigset_t *);
int (*__libc_poll)(struct pollfd *, nfds_t, int);
int (*__libc_ppoll)(struct pollfd *, nfds_t, const struct timespec *, const sigset_t *);
sighandler_t (*__libc_signal)(int, sighandler_t);
int (*__libc_sigaction)(int, const struct sigaction *, struct sigaction *);
int (*__libc_siginterrupt)(int, int);
int (*__libc_epoll_create)(int);
int (*__libc_epoll_create1)(int);
int (*__libc_epoll_ctl)(int, int, int, struct epoll_event *);
int (*__libc_epoll_wait)(int, struct epoll_event *, int, int);
int (*__libc_epoll_pwait)(int, struct epoll_event *, int, int, const sigset_t *);

__attribute__((constructor)) void load_func() {
    if (!__override_initialized) {
        __libc_socket = dlsym(RTLD_NEXT, "socket");
        __libc_close = dlsym(RTLD_NEXT, "close");
        __libc_bind = dlsym(RTLD_NEXT, "bind");
        __libc_listen = dlsym(RTLD_NEXT, "listen");
        __libc_accept = dlsym(RTLD_NEXT, "accept");
        __libc_accept4 = dlsym(RTLD_NEXT, "accept4");
        __libc_connect = dlsym(RTLD_NEXT, "connect");
        __libc_shutdown = dlsym(RTLD_NEXT, "shutdown");
        __libc_fcntl = dlsym(RTLD_NEXT, "fcntl");
        __libc_ioctl = dlsym(RTLD_NEXT, "ioctl");
        __libc_getsockname = dlsym(RTLD_NEXT, "getsockname");
        __libc_getpeername = dlsym(RTLD_NEXT, "getpeername");
        __libc_getsockopt = dlsym(RTLD_NEXT, "getsockopt");
        __libc_setsockopt = dlsym(RTLD_NEXT, "setsockopt");
        __libc_recv = dlsym(RTLD_NEXT, "recv");
        __libc_recvfrom = dlsym(RTLD_NEXT, "recvfrom");
        __libc_recvmsg = dlsym(RTLD_NEXT, "recvmsg");
        __libc_send = dlsym(RTLD_NEXT, "send");
        __libc_sendto = dlsym(RTLD_NEXT, "sendto");
        __libc_sendmsg = dlsym(RTLD_NEXT, "sendmsg");
        __libc_read = dlsym(RTLD_NEXT, "read");
        __libc_readv = dlsym(RTLD_NEXT, "readv");
        __libc_write = dlsym(RTLD_NEXT, "write");
        __libc_writev = dlsym(RTLD_NEXT, "writev");
        __libc_select = dlsym(RTLD_NEXT, "select");
        __libc_pselect = dlsym(RTLD_NEXT, "pselect");
        __libc_poll = dlsym(RTLD_NEXT, "poll");
        __libc_ppoll = dlsym(RTLD_NEXT, "ppoll");
        __libc_signal = dlsym(RTLD_NEXT, "signal");
        __libc_sigaction = dlsym(RTLD_NEXT, "sigaction");
        __libc_siginterrupt = dlsym(RTLD_NEXT, "siginterrupt");
        __libc_epoll_create = dlsym(RTLD_NEXT, "epoll_create");
        __libc_epoll_create1 = dlsym(RTLD_NEXT, "epoll_create1");
        __libc_epoll_ctl = dlsym(RTLD_NEXT, "epoll_ctl");
        __libc_epoll_wait = dlsym(RTLD_NEXT, "epoll_wait");
        __libc_epoll_pwait = dlsym(RTLD_NEXT, "epoll_pwait");

        __override_initialized = true;
        printf("load net call intercept finish\n");
    }
}

#define LIBC(func, ...) ({ __libc_##func(__VA_ARGS__); })

__attribute__((visibility("default"))) int socket(int domain, int type, int protocol) {
    printf("socket domain=%d, type=%d, protocol=%d\n", domain, type, protocol);
    return LIBC(socket, domain, type, protocol);
}

__attribute__((visibility("default"))) int close(int fd) {
    printf("close fd=%d\n", fd);
    return LIBC(close, fd);
}

__attribute__((visibility("default"))) int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen) {
    printf("bind sockfd=%d\n", sockfd);
    return LIBC(bind, sockfd, addr, addrlen);
}

__attribute__((visibility("default"))) int listen(int sockfd, int backlog) {
    printf("listen sockfd=%d, backlog=%d\n", sockfd, backlog);
    return LIBC(listen, sockfd, backlog);
}

__attribute__((visibility("default"))) int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen) {
    printf("accept sockfd=%d\n", sockfd);
    return LIBC(accept, sockfd, addr, addrlen);
}

__attribute__((visibility("default"))) int accept4(int sockfd, struct sockaddr *addr, socklen_t *addrlen, int flags) {
    printf("accept4 sockfd=%d, flags=%d\n", sockfd, flags);
    return LIBC(accept4, sockfd, addr, addrlen, flags);
}

__attribute__((visibility("default"))) int connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen) {
    printf("connect sockfd=%d\n", sockfd);
    return LIBC(connect, sockfd, addr, addrlen);
}

__attribute__((visibility("default"))) int shutdown(int sockfd, int how) {
    printf("shutdown sockfd=%d, how=%d\n", sockfd, how);
    return LIBC(shutdown, sockfd, how);
}

__attribute__((visibility("default"))) int fcntl(int fd, int cmd, ... /* arg */) {
    printf("fcntl fd=%d, cmd=%d\n", fd, cmd);
    int ret;
    va_list ap;
    va_start(ap, cmd);
    switch (cmd) {
        case F_GETFD:
        case F_GETFL:
        case F_GETOWN:
        case F_GETSIG:
        case F_GETLEASE:
            /* arg is void */
            ret = LIBC(fcntl, fd, cmd);
            break;
        case F_SETLK:
        case F_SETLKW:
        case F_GETLK:
            /* arg is pointer */
            ret = LIBC(fcntl, fd, cmd, va_arg(ap, void *));
            break;
        default:
            /* arg is long */
            ret = LIBC(fcntl, fd, cmd, va_arg(ap, long));
            break;
    }
    va_end(ap);
    return ret;
}

__attribute__((visibility("default"))) int ioctl(int fd, unsigned long int request, ...) {
    printf("ioctl sockfd=%d, request=%zu\n", fd, request);
    int ret;
    va_list ap;
    va_start(ap, request);
    ret = LIBC(ioctl, fd, request, va_arg(ap, void *));
    va_end(ap);
    return ret;
}

__attribute__((visibility("default"))) int getsockname(int sockfd, struct sockaddr *addr, socklen_t *addrlen) {
    printf("getsockname sockfd=%d\n", sockfd);
    return LIBC(getsockname, sockfd, addr, addrlen);
}

__attribute__((visibility("default"))) int getpeername(int sockfd, struct sockaddr *addr, socklen_t *addrlen) {
    printf("getpeername sockfd=%d\n", sockfd);
    return LIBC(getpeername, sockfd, addr, addrlen);
}

__attribute__((visibility("default"))) int getsockopt(int sockfd, int level, int optname, void *optval,
                                                      socklen_t *optlen) {
    printf("getsockopt sockfd=%d, level=%d, optname=%d\n", sockfd, level, optname);
    return LIBC(getsockopt, sockfd, level, optname, optval, optlen);
}

__attribute__((visibility("default"))) int setsockopt(int sockfd, int level, int optname, const void *optval,
                                                      socklen_t optlen) {
    printf("setsockopt sockfd=%d, level=%d, optname=%d\n", sockfd, level, optname);
    return LIBC(setsockopt, sockfd, level, optname, optval, optlen);
}

__attribute__((visibility("default"))) ssize_t recv(int sockfd, void *buf, size_t len, int flags) {
    printf("recv sockfd=%d, len=%zu, flags=%d\n", sockfd, len, flags);
    return LIBC(recv, sockfd, buf, len, flags);
}

__attribute__((visibility("default"))) ssize_t recvfrom(int sockfd, void *buf, size_t len, int flags,
                                                        struct sockaddr *src_addr, socklen_t *addrlen) {
    printf("recvfrom sockfd=%d, len=%zu, flags=%d\n", sockfd, len, flags);
    return LIBC(recvfrom, sockfd, buf, len, flags, src_addr, addrlen);
}

__attribute__((visibility("default"))) ssize_t recvmsg(int sockfd, struct msghdr *msg, int flags) {
    printf("recvmsg sockfd=%d, flags=%d\n", sockfd, flags);
    return LIBC(recvmsg, sockfd, msg, flags);
}

__attribute__((visibility("default"))) ssize_t read(int fd, void *buf, size_t count) {
    printf("read sockfd=%d, count=%zu\n", fd, count);
    return LIBC(read, fd, buf, count);
}

__attribute__((visibility("default"))) ssize_t readv(int fd, const struct iovec *iov, int iovcnt) {
    printf("readv sockfd=%d, iovcnt=%d\n", fd, iovcnt);
    return LIBC(readv, fd, iov, iovcnt);
}

__attribute__((visibility("default"))) ssize_t send(int sockfd, const void *buf, size_t len, int flags) {
    printf("send sockfd=%d, len=%zu, flags=%d\n", sockfd, len, flags);
    return LIBC(send, sockfd, buf, len, flags);
}

__attribute__((visibility("default"))) ssize_t sendto(int sockfd, const void *buf, size_t len, int flags,
                                                      const struct sockaddr *dest_addr, socklen_t addrlen) {
    printf("sendto sockfd=%d, len=%zu, flags=%d\n", sockfd, len, flags);
    return LIBC(sendto, sockfd, buf, len, flags, dest_addr, addrlen);
}

__attribute__((visibility("default"))) ssize_t sendmsg(int sockfd, const struct msghdr *msg, int flags) {
    printf("sendmsg sockfd=%d, flags=%d\n", sockfd, flags);
    return LIBC(sendmsg, sockfd, msg, flags);
}

__attribute__((visibility("default"))) ssize_t write(int fd, const void *buf, size_t count) {
    printf("write sockfd=%d, count=%zu\n", fd, count);
    return LIBC(write, fd, buf, count);
}

__attribute__((visibility("default"))) ssize_t writev(int fd, const struct iovec *iov, int iovcnt) {
    printf("write sockfd=%d, iovcnt=%d\n", fd, iovcnt);
    return LIBC(writev, fd, iov, iovcnt);
}

__attribute__((visibility("default"))) int select(int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds,
                                                  struct timeval *timeout) {
    printf("select sockfd=%d\n", nfds);
    return LIBC(select, nfds, readfds, writefds, exceptfds, timeout);
}

__attribute__((visibility("default"))) int pselect(int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds,
                                                   const struct timespec *timeout, const sigset_t *sigmask) {
    printf("pselect sockfd=%d\n", nfds);
    return LIBC(pselect, nfds, readfds, writefds, exceptfds, timeout, sigmask);
}

__attribute__((visibility("default"))) int poll(struct pollfd *fds, nfds_t nfds, int timeout) {
    printf("poll nfds=%zu, timeout=%d\n", nfds, timeout);
    return LIBC(poll, fds, nfds, timeout);
}

__attribute__((visibility("default"))) int ppoll(struct pollfd *fds, nfds_t nfds, const struct timespec *timeout,
                                                 const sigset_t *sigmask) {
    printf("ppoll nfds=%zu\n", nfds);
    return LIBC(ppoll, fds, nfds, timeout, sigmask);
}

__attribute__((visibility("default"))) sighandler_t signal(int signum, sighandler_t handler) {
    printf("signal signum=%d\n", signum);
    return LIBC(signal, signum, handler);
}

__attribute__((visibility("default"))) int sigaction(int signum, const struct sigaction *act,
                                                     struct sigaction *oldact) {
    printf("sigaction signum=%d\n", signum);
    return LIBC(sigaction, signum, act, NULL);
}

__attribute__((visibility("default"))) int siginterrupt(int signum, int flag) {
    printf("siginterrupt signum=%d, flag=%d\n", signum, flag);
    return LIBC(siginterrupt, signum, flag);
}

__attribute__((visibility("default"))) int epoll_create(int size) {
    printf("epoll_create size=%d\n", size);
    return LIBC(epoll_create, size);
}

__attribute__((visibility("default"))) int epoll_create1(int flags) {
    printf("epoll_create1 flags=%d\n", flags);
    return LIBC(epoll_create1, flags);
}

__attribute__((visibility("default"))) int epoll_ctl(int epfd, int op, int fd, struct epoll_event *event) {
    printf("epoll_ctl epfd=%d, op=%d, fd=%d\n", epfd, op, fd);
    return LIBC(epoll_ctl, epfd, op, fd, event);
}

__attribute__((visibility("default"))) int epoll_wait(int epfd, struct epoll_event *events, int maxevents,
                                                      int timeout) {
    printf("epoll_wait epfd=%d, maxevents=%d, timeout=%d\n", epfd, maxevents, timeout);
    return LIBC(epoll_wait, epfd, events, maxevents, timeout);
}

__attribute__((visibility("default"))) int epoll_pwait(int epfd, struct epoll_event *events, int maxevents, int timeout,
                                                       const sigset_t *sigmask) {
    printf("epoll_pwait epfd=%d, maxevents=%d, timeout=%d\n", epfd, maxevents, timeout);
    return LIBC(epoll_pwait, epfd, events, maxevents, timeout, sigmask);
}
