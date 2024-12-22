#include "common.h"

int main(int argc,char* argv[]){
    int serv_sock;
    int clnt_sock;

    struct sockaddr_in serv_addr;
    struct sockaddr_in clnt_addr;
    socklen_t clnt_addr_size;

    char msg[] = "hello world";
    if(argc != 2){
        printf("Usage : %s <port>\n", argv[0]);
        exit(1);
    }

    serv_sock = socket(PF_INET,SOCK_STREAM, 0);
    if(serv_sock == -1)
        Common::error_handling("socket() error");
    int opt = 1; 
    int err = setsockopt(serv_sock,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));
    if( err )
    {
        Common::error_handling("setsockopt failed");
    }
    memset(&serv_addr,0,sizeof(serv_addr));
    serv_addr.sin_family=AF_INET;
    serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);
    serv_addr.sin_port=htons(atoi(argv[1]));

    if(bind(serv_sock,(struct sockaddr*)&serv_addr,sizeof(serv_addr)) == -1){
        Common::error_handling("Bind() error");
    }

    if(listen(serv_sock,5) == -1){
        Common::error_handling("listen() error");
    }
    clnt_addr_size = sizeof(clnt_addr);
    clnt_sock=accept(serv_sock,(struct sockaddr*)&clnt_addr,&clnt_addr_size);
    if(clnt_sock == -1){
        Common::error_handling("accept() error");
    }

    write(clnt_sock,msg,sizeof(msg));
    close(clnt_sock);
    close(serv_sock);
    return 0;
}