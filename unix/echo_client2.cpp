#include "common.h"

constexpr int BUF_SIZE = 100;
int main(int argc,char* argv[]){
    int sock;
    char message[BUF_SIZE];
    int str_len,recv_len,recv_cnt;
    struct sockaddr_in serv_adr;
    if(argc != 3){
        printf("Usage : %s <IP> <port>\n",argv[0]);
        exit(1);
    }

    sock=socket(PF_INET,SOCK_STREAM,0);
    if(sock == -1){
        Common::error_handling("socket() error");
    }

    memset(&serv_adr,0,sizeof(serv_adr));
    serv_adr.sin_family=AF_INET;
    serv_adr.sin_addr.s_addr=inet_addr(argv[1]);
    serv_adr.sin_port=htons(atoi(argv[2]));

    if(connect(sock,(struct  sockaddr*)&serv_adr,sizeof(serv_adr)) == -1){
        Common::error_handling("connect() error!");
    } else {
        puts("Connected............");
    }

    while(1){
        fputs("Input message (Q to quit): ",stdout);
        fgets(message,BUF_SIZE,stdin);
        if(!strcmp(message,"q\n") || !strcmp(message,"Q\n")){
            break;
        }

        str_len = write(sock,message,strlen(message));

        recv_len=0;
        while(recv_len<str_len){
            recv_cnt=read(sock,&message[recv_len],BUF_SIZE-1);
            if(recv_cnt == -1){
                Common::error_handling("read() error!");
            }
            recv_len += recv_cnt;
        }

        message[recv_len] = 0;
        printf("Message from server: %s",message);
    }
    close(sock);
    return 0;
}