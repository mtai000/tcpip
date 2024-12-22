#include "common.h"

constexpr int BUF_SIZE = 30;

int main(int argc,char* argv[]){
    int send_sock;
    struct sockaddr_in broad_adr;
    FILE *fp;
    char buf[BUF_SIZE];
    int so_brd = 1;
    if(argc != 3) {
        printf("Usage : %s <Boradcast IP> <port> \n",argv[0]);
        exit(1);
    }

    send_sock=socket(PF_INET,SOCK_DGRAM,0);
    memset(&broad_adr,0,sizeof(broad_adr));
    broad_adr.sin_family=AF_INET;
    broad_adr.sin_addr.s_addr=inet_addr(argv[1]);
    broad_adr.sin_port=htons(atoi(argv[2]));

    setsockopt(send_sock,SOL_SOCKET,SO_BROADCAST,(void*)&so_brd,sizeof(so_brd));

    if((fp=fopen("news.txt","r"))==NULL){
        Common::error_handling("fopen() error");
    }

    while(!feof(fp)){
        fgets(buf,BUF_SIZE,fp);
        sendto(send_sock,buf,strlen(buf),0,(struct sockaddr*)&broad_adr,sizeof(broad_adr));
        sleep(2);

    }
    close(send_sock);
    return 0;
}