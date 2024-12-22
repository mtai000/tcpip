#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include "common.h"

int main(int argc,char *argv[]){
    char* addr = "127.232.124.79";
    struct sockaddr_in addr_inet;
    
    if(!inet_aton(addr,&addr_inet.sin_addr)){
        Common::error_handling("Coversion error");
    } else {
        printf("Network ordered integer addr: %#lx \n",addr_inet.sin_addr.s_addr);
    }
    return 0;
}