#include "common.h"
#include <netdb.h>

int main(int argc,char* argv[]){
    int i;
    struct hostent *host;
    if(argc!=2){
        printf("Usage : %s <addr>\n",argv[0]);
        exit(1);
    }

    host=gethostbyname(argv[1]);
    if(!host){
        Common::error_handling("gethost ... error");
    }
    
    printf("Official name: %s \n",host->h_name);
    for(i = 0 ; host->h_aliases[i];i++){
        printf("Aliases %s: %s \n", i + 1, host->h_aliases[i]);
    }
    printf("Address type: %s \n",(host->h_addrtype==AF_INET)?"AF_INET":"AF_INET6");
    for(i = 0; host->h_addr_list[i];i++){
        printf("IP addr %d: %s \n",i+1,inet_ntoa(*(struct in_addr*)host->h_addr_list[i]));
    }
    return 0;
}