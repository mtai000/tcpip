#include "common.h"
#include <pthread.h>
constexpr int BUF_SIZE = 100;
constexpr int MAX_CLNT = 256;

void* handle_clnt(void* arg);
void send_msg(char* msg, int len);
int clnt_cnt = 0;
int clnt_socks[MAX_CLNT];
pthread_mutex_t mutex;

int main(int argc,char* argv[]){
    int serv_sock,clnt_sock;
    sockaddr_in serv_adr,clnt_adr;
    socklen_t clnt_adr_sz;
    pthread_t t_id;
    if(argc != 2){
        printf("Usage : %s <port> \n",argv[0]);
        exit(1);
    }

    pthread_mutex_init(&mutex,NULL);
    serv_sock=socket(PF_INET,SOCK_STREAM,0);
    memset(&serv_adr,0,sizeof(serv_adr));
    serv_adr.sin_family=AF_INET;
    serv_adr.sin_addr.s_addr=htonl(INADDR_ANY);
    serv_adr.sin_port=htons(atoi(argv[1]));

    if(bind(serv_sock,(sockaddr*)&serv_adr,sizeof(serv_adr)) == -1){
        Common::error_handling("bind() error");
    }
    if(listen(serv_sock,5) == -1){
        Common::error_handling("listen() error");
    }

    while(1){
        clnt_adr_sz = sizeof(clnt_adr);
        clnt_sock=accept(serv_sock,(sockaddr*)&clnt_adr , &clnt_adr_sz);

        pthread_mutex_lock(&mutex);
        clnt_socks[clnt_cnt++]=clnt_sock;
        pthread_mutex_unlock(&mutex);

        pthread_create(&t_id,NULL,handle_clnt,(void*)&clnt_sock);
        pthread_detach(t_id);
        printf("Connected client IP: %s \n",inet_ntoa(clnt_adr.sin_addr));
    }
    close(serv_sock);
    return 0;
}

void* handle_clnt(void* arg){
    int clnt_sock=*((int*)arg);
    int str_len = 0;
    char msg[BUF_SIZE];
    while((str_len=read(clnt_sock,msg,sizeof(msg))) != 0){
        send_msg(msg,str_len);
    }

    pthread_mutex_lock(&mutex);
    for(int i = 0; i < clnt_cnt; i++){
        if(clnt_sock == clnt_socks[i]){
            while( i++ < clnt_cnt - 1){
                clnt_socks[i] = clnt_socks[i+1];
            }
            break;
        }
    }

    clnt_cnt--;
    pthread_mutex_unlock(&mutex);
    close(clnt_sock);
    return NULL;
}

void send_msg(char* msg,int len){
    pthread_mutex_lock(&mutex);
    for(int i = 0; i < clnt_cnt; i++){
        write(clnt_socks[i],msg,len);
    }
    pthread_mutex_unlock(&mutex);
}