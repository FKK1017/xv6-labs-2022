#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[]) {
    int p[2];
    pipe(p);
    if (fork()==0) {
        close(p[1]);
        int num, x;
        while (1) {
            int fd[2];
            pipe(fd);
            read(p[0], &num, sizeof(int));
            printf("prime %d\n", num);
            if (fork()!=0 || num==35) {
                close(fd[0]);
                while (num!=35) {
                    read(p[0], &x, sizeof(int));
                    if (x%num!=0 || x==35) {
                        write(fd[1], &x, sizeof(int));
                    }
                    if (x==35) {
                        break;
                    }
                }
                close(p[0]);
                close(fd[1]);
                wait(0);
                exit(0);
            } else {
                close(p[0]);
                p[0] = fd[0];
                close(fd[1]);
            }
        }
    } else {
        close(p[0]);
        for (int i=2; i<=35; i++) {
            write(p[1], &i, sizeof(int));
        }
        wait(0);
    }
    exit(0);
}