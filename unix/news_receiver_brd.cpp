#include "common.h"

constexpr int BUF_SIZE = 30;

int main(int argc,char* argv[]){
    if(argc != 2){
        printf("Usage : %s <port>\n",argv[0]);
        exit(1);
    }

    int recv_sock=socket(PF_INET,SOCK_DGRAM,0);
    struct sockaddr_in adr;
    memset(&adr,0,sizeof(adr));
    adr.sin_family=AF_INET;
    adr.sin_addr.s_addr=htonl(INADDR_ANY);
    adr.sin_port=htons(atoi(argv[1]));

    if(bind(recv_sock,(struct sockaddr*)&adr,sizeof(adr)) == -1){
        Common::error_handling("bind() error");
    }

    int str_len;
    char buf[BUF_SIZE];
    while(1){
        str_len = recvfrom(recv_sock,buf,BUF_SIZE - 1, 0, NULL, 0);
        if(str_len < 0){
            break;
        }
        buf[str_len] = 0;
        fputs(buf,stdout);
    }
    close(recv_sock);
    return 0;
}