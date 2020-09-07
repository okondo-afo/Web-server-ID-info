#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h> 
#include <stdio.h>
#include <netdb.h>


#define PORT 80 
#include "hacking.h"
#include "new.h"


char main(int argc, char *argv[]) {

if(argc < 2){
printf("USAAGE:: Programe webname OR hostname\n ---- made by jadu ----\n");
exit(0) ; 
}
int sock, check;
struct sockaddr_in  targ ;
struct hostent *targ_ip ; 
char data ;
void *head = "HEAD / HTTP/1.0\r\n";
unsigned char buffer[5000];

socklen_t sin_size ;

targ_ip = gethostbyname(argv[1]) ; 
if(!targ_ip){
printf("could not resolve hostname\ncheck your internet connection also check if the webname is correct\n") ; 
exit(0) ; 
}
else{
if((sock = socket(PF_INET,SOCK_STREAM,0)) == -1){
fatal("while opening socket");
}

targ.sin_family = AF_INET ; 
targ.sin_port = htons(PORT) ; 
targ.sin_addr = *((struct in_addr *)targ_ip->h_addr) ; 
memset(&(targ.sin_zero),'\0',8); 

printf("%s IP ADDRESS IS %s\n", argv[1],inet_ntoa(targ.sin_addr));

printf("\nNow Connecting to %s\n", argv[1]);

sin_size = sizeof(struct sockaddr) ; 
if( connect(sock,(struct sockaddr *)&targ,sizeof(struct sockaddr)) == -1) {
fatal("in connect()") ; 
exit(0) ; 
}

else{
printf("\nConnected to %s\n" ,argv[1]);
sendstr(sock,"HEAD / HTTP/1.0\r\n\r\n");
while(check = recv_data(sock,buffer)){

if(check == 1){
printf("\n%s", buffer);
 }
}
printf("\n-------- MADE BY JADU -----\n") ;
exit(0);
}


    


}
}

