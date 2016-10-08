#include <sys/types.h>
#include <sys/mman.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFSIZE 8192

int main() {
    int fd, i;
    char *addr;
    fd = open("data.txt", O_RDWR, 0644);
    addr = mmap(0, BUFSIZE, (PROT_READ | PROT_WRITE), MAP_SHARED, fd, 0);
    write(1, addr, 20);
    memcpy(addr + 5, "hello", 5);
    return 0;
}