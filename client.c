#include<stdio.h>


#include<netinet/in.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netdb.h>


#include<string.h>
#include<stdlib.h>


#define MAX 80
#define PORT 43454
#define SA struct sockaddr


void shell(int sockfd){
    
    char buff[MAX];    
    int n;
    
    printf("Type linux terminal commands, here are some commands\n");
    
    for(;;){
        
        bzero(buff,sizeof(buff));
        
        printf("client@root$_: ");
        n=0;
        
        while((buff[n++]=getchar())!='\n');
        write(sockfd,buff,sizeof(buff));
        
    
        if((strncmp(buff,"exit",4))==0){
            printf("Client Exit;\n");
            break;
        }
        
        bzero(buff,sizeof(buff));
        
        read(sockfd,buff,sizeof(buff));
        printf("server@root$_: %s\n",buff);
    }
}

int main(){
    
    int sockfd,connfd;
    
    struct sockaddr_in servaddr,cli;    
    sockfd=socket(AF_INET,SOCK_STREAM,0);
    
    if(sockfd==-1){ 
        printf("Socket creation failed - Client Side\n");
        exit(0);
    }
    else
        printf("Socket successfully created - Client Side\n");
    bzero(&servaddr,sizeof(servaddr));
    servaddr.sin_family=AF_INET;
    servaddr.sin_addr.s_addr=inet_addr("127.0.0.1");
    servaddr.sin_port=htons(PORT);
    
    if(connect(sockfd,(SA *)&servaddr,sizeof(servaddr))!=0) {
   
        printf("Connection with the server failed - Client Side\n");
        exit(0);
    }
    else
        printf("Connected to the server - Client Side\n");
    shell(sockfd);
    close(sockfd);
}
