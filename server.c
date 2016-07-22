#include<stdio.h>

#include<netinet/in.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netdb.h>

#include<stdlib.h>
#include<string.h>

#define MESSAGEMAXSIZE 80
#define PORTNUMBER 43454
#define SA struct sockaddr



void shell(int sockfd){
    
    char buff[MESSAGEMAXSIZE];
    int n;
    //Infinite loop, stops when exit is typed like a normal terminal
    for(;;){
        //converts all buffers position value to zerp
        bzero(buff,MESSAGEMAXSIZE);
        
        // read incoming message 
        read(sockfd,buff,sizeof(buff));
        printf("client@root$_ %s",buff);
        bzero(buff,MESSAGEMAXSIZE);
        n=0;
       // while((buff[n++]=getchar())!='\n');
        //write server message
        write(sockfd,buff,sizeof(buff));       
        
    }
}


int main(){
    
    int sockfd,connfd,len;
    struct sockaddr_in servaddr,cli;
    sockfd=socket(AF_INET,SOCK_STREAM,0);
    if(sockfd==-1){
        printf("Socket creation failed - Server side;\n");
        exit(0);
    }
    else
        printf("Socket successfully created - Server side;\n");
    
    bzero(&servaddr,sizeof(servaddr));
    // Struct variables 
    servaddr.sin_family=AF_INET;
    servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
    servaddr.sin_port=htons(PORTNUMBER);
    
    if((bind(sockfd,(SA*)&servaddr, sizeof(servaddr)))!=0){
        printf("Socket bind failed - Server side;\n");
        exit(0);
    }   
    else
        printf("Socket binded - Server side;\n");
    
    if((listen(sockfd,5))!=0) {
   
        printf("Not able to listen - Server side;\n");
        exit(0);
    }
    else
        printf("Server listening - Server side;\n");
    
    len=sizeof(cli);
    connfd=accept(sockfd,(SA *)&cli,&len);
    
    if(connfd<0){

        printf("Server connection accceptance failed - Server side;\n");
        exit(0);
    }
    else
        printf("Server connected to the client successfully - Server side;\n");
    
    
    shell(connfd);
    close(sockfd);
}
