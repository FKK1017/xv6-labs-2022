#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[]) {
    int p[2];
    pipe(p);
    char c[2];
    if (fork()==0) {
        //chlid
        read(p[0], c, 1);
        if (*c=='f') {
            fprintf(2, "%d: received ping\n", getpid());
            write(p[1], "c", 1);
            exit(0);
        } else {
            exit(1);
        }
    } else {
        //father
        write(p[1], "f", 1);
        read(p[0], c, 1);
        if (*c=='c') {
            fprintf(2, "%d: received pong\n", getpid());
            exit(0);
        } else {
            exit(1);
        }
    }
}