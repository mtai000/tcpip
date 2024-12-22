#include "common.h"

constexpr int BUF_SIZE = 1024;
int main(int argc,char* argv[]){
    if(argc != 3){
        printf("Usage : %s <IP> <port>\n",argv[0]);
        exit(1);
    }
    int sock=socket(PF_INET,SOCK_STREAM,0);
    if(sock == -1){
        Common::error_handling("socket() error");
    }

    sockaddr_in serv_adr;
    FILE* readfp;
    FILE* writefp;
    memset(&serv_adr,0,sizeof(serv_adr));
    serv_adr.sin_family=AF_INET;
    serv_adr.sin_addr.s_addr=inet_addr(argv[1]);
    serv_adr.sin_port=htons(atoi(argv[2]));

    if(connect(sock,(sockaddr*)&serv_adr,sizeof(serv_adr)) == -1){
        Common::error_handling("connect() error!");
    } else {
        puts("Connect.....");
    }
    readfp=fdopen(sock,"r");
    writefp=fdopen(sock,"w");
 
    char message[BUF_SIZE];
    while(1){
        fputs("Input message(Q to quit):",stdout);
        fgets(message,BUF_SIZE,stdin);
        if(!strcmp(message,"q\n") || !strcmp(message,"Q\n")){
            break;
        }

        fputs(message,writefp);
        fflush(writefp);
        fgets(message,BUF_SIZE,readfp);
        printf("Message from server: %s",message);
    }

   return 0;
}