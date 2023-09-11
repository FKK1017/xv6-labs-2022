#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/param.h"

int readLine(char *buf) 
{
    char c;
    while (1)
    {
        if (read(0, &c, sizeof(char))!=0)
        {
            if (c=='\n' || c=='\r')
            {
                break;
            }
            *buf=c;
            buf++;
        }
        else 
        {
            return 0;
        }
    }
    *buf='\0';
    return 1;
}

int main(int argc, char *argv[])
{
    char buf[512], *args[MAXARG];
    memcpy(args, argv+1, (argc-1)*sizeof(char *));
    while (readLine(buf)) 
    {
        if (fork()==0)
        {
            args[argc-1] = buf;
            exec(args[0], args);
            exit(0);
        }
        else
        {
            wait(0);
        }
    }
    exit(0);
}