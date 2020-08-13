#include <fcntl.h>
#include <signal.h>
#include <sys/errno.h>
#include <sys/stat.h>
#include <unistd.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>

using namespace std;

constexpr int MAXPROCESS = 10;
constexpr int BUFFER = 4096;

struct action {
    string name;
    int (*function)(int, char*, char*);
};

int emit_increment(int lockFd, char* lockFile, char* pidFile);
int emit_decrement(int lockFd, char* lockFile, char* pidFile);
int emit_audit(int lockFd, char* lockFile, char* pidFile);

struct action actions[] = {
    {"increment", &emit_increment}, {"decrement", &emit_decrement}, {"audit", &emit_audit}, {"", nullptr}};

struct flock lock;
int pid;
int maxProcess = MAXPROCESS;
extern int errno;
string myName;

/**
 * return 0 if pid is 0 or it doesn't exit
 */
int pid_ok(pid_t p) {
    extern int errno;
    return (p == 0 || (kill(p, 0) && errno == ESRCH)) ? 0 : 1;
}

void check_stdio(FILE* f) {
    struct stat s;
    if (fstat(fileno(f), &s) < 0 && errno == EBADF) {
        auto ret = freopen("/dev/null", "w", f);
        if (ret < 0) fprintf(stderr, "freopen error %s\n", strerror(errno));
    }
}

int emit_lock(char* lockFile) {
    int fd;
    struct stat fs, s;
    lock.l_type = F_WRLCK;
    while (1) {
        if ((fd = open(lockFile, O_RDWR | O_CREAT, 0666)) < 0) {
            fprintf(stderr, "%s: open %s: %s\n", myName.c_str(), lockFile, strerror(errno));
            return -1;
        }

        while (fcntl(fd, F_SETLK, &lock)) {
            fprintf(stderr, "%s: fcntl %s: %s\n", myName.c_str(), lockFile, strerror(errno));
            sleep(1);
        }

        if (stat(lockFile, &s) < 0) {
            if (errno == ENOENT) {
                if (close(fd)) {
                    fprintf(stderr, "%s: close %s: %s\n", myName.c_str(), lockFile, strerror(errno));
                    return -1;
                }
                continue;
            }
            fprintf(stderr, "%s: stat %s: %s\n", myName.c_str(), lockFile, strerror(errno));
            return -1;
        }

        if (fstat(fd, &fs) < 0) {
            fprintf(stderr, "%s: fstat %s: %s\n", myName.c_str(), lockFile, strerror(errno));
            return -1;
        }

        if (fs.st_dev == s.st_dev && fs.st_ino == s.st_ino) break;

        if (close(fd)) {
            fprintf(stderr, "%s: close %s: %s\n", myName.c_str(), lockFile, strerror(errno));
            return -1;
        }
    }
    return fd;
}

/**
 * close given fd which free the lock, if count is 0, then remove it
 */
int emit_free(int fd, char* lockFile, int count) {
    if (count == 0 && unlink(lockFile)) {
        fprintf(stderr, "%s: unlink %s: %s\n", myName.c_str(), lockFile, strerror(errno));
    }

    if (close(fd)) {
        fprintf(stderr, "%s: close %s: %s\n", myName.c_str(), lockFile, strerror(errno));
        return -1;
    }
    return 0;
}

/**
 * read the lock file, return its content as an int
 */
int read_lock(int fd, char* lockFile) {
    char buf[BUFFER];
    ssize_t n;
    if ((n = read(fd, buf, BUFFER)) < 0) {
        fprintf(stderr, "%s: read %s: %s\n", myName.c_str(), lockFile, strerror(errno));
        return -1;
    }
    buf[n] = '\0';
    int r = atoi(buf);
    return r > 0 ? r : 0;
}

/**
 * open the lock file, truncate write the count into lockFile
 */
int write_lock(int fd, char* lockFile, int count) {
    char buf[BUFFER];
    if (ftruncate(fd, 0) < 0) {
        fprintf(stderr, "%s: ftruncate %s: %s\n", myName.c_str(), lockFile, strerror(errno));
        return -1;
    }
    if (lseek(fd, 0, SEEK_SET) < 0) {
        fprintf(stderr, "%s: lseek %s: %s\n", myName.c_str(), lockFile, strerror(errno));
        return -1;
    }

    sprintf(buf, "%d\n", count);
    if (write(fd, buf, strlen(buf)) < 0) {
        fprintf(stderr, "%s: write %s: %s\n", myName.c_str(), lockFile, strerror(errno));
        return -1;
    }
    return 0;
}

/**
 * read the pid file, return array of pids
 */
int* read_pids(char* pidFile) {
    char buf[BUFFER];
    int n = 1000, npids = 0;
    int* pids{nullptr};
    FILE* f{nullptr};
    if ((pids = (int*)malloc((n + 2) * sizeof(int))) == nullptr) {
        perror("malloc failed");
        return nullptr;
    }
    if ((f = fopen(pidFile, "r")) == nullptr) {
        pids[0] = -1;
        return pids;
    }
    while (fgets(buf, BUFFER, f)) {
        int p;
        if (n < npids) {
            n += npids;
            if ((pids = (int*)realloc(pids, (n + 2) * sizeof(int))) == nullptr) {
                perror("realloc failed");
                return nullptr;
            }
        }

        if ((p = atoi(buf))) {
            pids[npids++] = p;
        } else {
            auto l = strlen(buf);
            if (buf[l - 1] == '\n') buf[l - 1] = '\0';
            fprintf(stderr, "%s: ignore bad pidFile line %s\n", myName.c_str(), buf);
        }
    }
    pids[npids] = -1;
    if (fclose(f)) {
        fprintf(stderr, "%s: fclose %s: %s\n", myName.c_str(), pidFile, strerror(errno));
        free(pids);
        return nullptr;
    }
    return pids;
}

/**
 * open the pid file, write pids into pidFile and return the number of pids written
 */
int write_pids(int* pids, char* pidFile) {
    FILE* f{nullptr};
    int npids = 0;
    if ((f = fopen(pidFile, "w")) == nullptr) {
        fprintf(stderr, "%s: fopen %s: %s\n", myName.c_str(), pidFile, strerror(errno));
        return -1;
    }

    for (size_t i = 0; pids[i] >= 0; i++) {
        if (pids[i] > 0) {
            fprintf(f, "%d\n", pids[i]);
            npids++;
        }
    }

    if (fclose(f)) {
        fprintf(stderr, "%s: fclose %s: %s\n", myName.c_str(), pidFile, strerror(errno));
        return -1;
    }

    // if no more pid, then remove pid file
    if (npids == 0 && unlink(pidFile) == -1 && errno != ENOENT) {
        fprintf(stderr, "%s: unlink %s: %s\n", myName.c_str(), pidFile, strerror(errno));
        return -1;
    }
    return npids;
}

/**
 * increment lockFile count, and write new pid to pidFile
 */
int emit_increment(int fd, char* lockFile, char* pidFile) {
    int count;
    int* pids{nullptr};
    int r;

    if ((count = read_lock(fd, lockFile)) < 0) return count;

    if (maxProcess > 0 && count >= maxProcess) return -6;

    count++;

    if ((pids = read_pids(pidFile)) == nullptr) return -1;

    size_t i = 0;
    for (; pids[i] >= 0; i++) {
        if (!pid_ok(pids[i])) {
            fprintf(stderr, "%s: remove bad pids %d\n", myName.c_str(), pids[i]);
            pids[i] = 0;
        }
    }

    // add our pid
    pids[i++] = pid;
    pids[i] = -1;

    if (write_lock(fd, lockFile, count) < 0) return -1;

    if ((r = write_pids(pids, pidFile)) < 0) return -1;

    if (r != count) {
        fprintf(stderr, "%s: lock file contains %d and pidFile contains %d good entries\n", myName.c_str(), count, r);
    }
    return count;
}

/**
 * decrement lockFile count, and remove the old pid from pidFile
 */
int emit_decrement(int fd, char* lockFile, char* pidFile) {
    int count;
    int* pids{nullptr};
    int r;

    if ((count = read_lock(fd, lockFile)) < 0) return -1;

    if (count > 0) count--;

    if ((pids = read_pids(pidFile)) == nullptr) return -1;

    for (size_t i = 0; pids[i] >= 0; i++) {
        if (!pid_ok(pids[i])) {
            fprintf(stderr, "%s: remove bad pids %d\n", myName.c_str(), pids[i]);
            pids[i] = 0;
        } else if (pids[i] == pid) {
            pids[i] = 0;
        }
    }

    if (write_lock(fd, lockFile, count) < 0) return -1;

    if ((r = write_pids(pids, pidFile)) < 0) return -1;

    if (r != count) {
        fprintf(stderr, "%s: lock file contains %d and pidFile contains %d good entries\n", myName.c_str(), count, r);
    }
    return count;
}

/**
 * report bad pids
 */
int emit_audit(int fd, char* lockFile, char* pidFile) {
    int count;
    int* pids{nullptr};
    int r{0};

    if ((count = read_lock(fd, lockFile)) < 0) return -1;

    if ((pids = read_pids(pidFile)) == nullptr) return -1;

    for (size_t i = 0; pids[i] >= 0; i++) {
        if (!pid_ok(pids[i])) {
            fprintf(stderr, "%s: found bad pids %d\n", myName.c_str(), pids[i]);
        } else {
            r++;
        }
    }

    if (r != count) {
        fprintf(stderr, "%s: lock file contains %d and pidFile contains %d good entries\n", myName.c_str(), count, r);
    }
    return count;
}

int main(int argc, char* argv[]) {
    char* lockFile;
    char* pidFile;
    int c, r;
    extern char* optarg;
    extern int optind;
    int fd;
    struct action* ap;

    check_stdio(stdout);
    check_stdio(stderr);

    pid = getpid();
    umask(0111);

    while ((c = getopt(argc, argv, "a:m:p:")) != EOF) {
        switch (c) {
            case 'a':
                myName = string(optarg);
                break;
            case 'm':
                maxProcess = atoi(optarg);
                break;
            case 'p':
                pid = atoi(optarg);
                break;
            default:
                fprintf(stderr, "%s: usage: %s [-m maxprocess] [-p pid] lockFile pidFile\n", myName.c_str(),
                        myName.c_str());
                exit(2);
        }
    }

    for (ap = actions; !(ap->name.empty()); ap++) {
        if (myName == ap->name) break;
    }

    if (ap->name.empty()) {
        printf("no such command %s\n", myName.c_str());
        exit(2);
    }

    if (optind + 2 != argc) {
        fprintf(stderr, "%s: usage: emit -a action [-m maxprocess] [-p pid] lockFile pidFile\n", myName.c_str());
        exit(1);
    }
    lockFile = argv[optind++];
    pidFile = argv[optind++];

    if ((fd = emit_lock(lockFile)) < 0) exit(1);

    r = ap->function(fd, lockFile, pidFile);

    if (emit_free(fd, lockFile, r) < 0) exit(1);
    return (r < 0 ? -r : 0);
}
