#include "common.h"

void Common::error_handling(char *message)
{
    fputs(message,stderr);
    fputc('\n',stderr);
    exit(1); 
}

void Common::read_childproc(int sig){
    pid_t pid;
    int status;
    pid=waitpid(-1,&status,WNOHANG);
    printf("removed proc id : %d\n",pid);
}