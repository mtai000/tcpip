#include "common.h"

constexpr int BUF_SIZE = 1024;

int main(int argc,char* argv[]){
    if(argc != 2){
        printf("Usage : %s <port>\n",argv[0]);
        exit(1);
    }

    int serv_sock=socket(PF_INET,SOCK_STREAM,0);
    if(serv_sock == -1){
        Common::error_handling("socket() error");
    }

    sockaddr_in serv_adr,clnt_adr;
    memset(&serv_adr,0,sizeof(serv_adr));
    serv_adr.sin_family=AF_INET;
    serv_adr.sin_addr.s_addr=htonl(INADDR_ANY);
    serv_adr.sin_port=htons(atoi(argv[1]));

    if(bind(serv_sock,(struct sockaddr*)&serv_adr,sizeof(serv_adr)) == -1){
        Common::error_handling("bind() error");
    }
    if(listen(serv_sock,5) == -1){
        Common::error_handling("listen() error");
    }

    socklen_t clnt_adr_sz=sizeof(clnt_adr);
    int clnt_sock;
    FILE* readfp;
    FILE* writefp;
    char message[BUF_SIZE];
    for(int i = 0; i < 5; i++){
        clnt_sock=accept(serv_sock,(sockaddr*)&clnt_adr,&clnt_adr_sz);
        if(clnt_sock == -1){
            Common::error_handling("accept() error");
        }

        readfp=fdopen(clnt_sock,"r");
        writefp=fdopen(clnt_sock,"w");
        while(!feof(readfp)){
            fgets(message,BUF_SIZE,readfp);
            fputs(message,writefp);
            fflush(writefp);
        }
        fclose(readfp);
        fclose(writefp);
    }
    close(serv_sock);
    return 0;
}