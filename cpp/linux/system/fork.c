#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    int pid, number = 0, status, fd;
    printf("before fork...\n");
    pid = fork();
    if(pid == 0){
        printf("hello from child\n");

        fd = open("out.txt", O_WRONLY | O_CREAT, 0664);
        status = dup2(fd, 1);
        close(fd);
        execlp("ls", "ls", NULL);
    } else {
        printf("hello from parent\n");
        number = 50;
    }
    printf("from parent\n");
    printf("number is %d\n", number);

    pid = wait(&status);
    return 0;
}