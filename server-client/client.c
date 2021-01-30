//
// Created by qwerty on 12.01.2021.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include "serverClient.h"
#include <unistd.h>
#define SIZE 2048
#define MAX 5


void main(int argc,char** argv)
{
    int sock,c;
    struct sockaddr_in server;

    char* message=malloc(sizeof(char)*SIZE);
    char* sending=malloc(sizeof(char)*SIZE);

    if(argc<3)
    {
        fprintf(stderr,"[-] Usage: %s <ip Address> <port Number>\n",argv[0]);
        exit(EXIT_FAILURE);
    }

    FILE* f=fopen("client_log.txt","a");

    if(!f)perror("File is not created....\n");

    printf("Dou you want to log?\n1-Yes\n2-No\n");
    scanf("%d",&c);

    if(c==2)
        remove("client_log.txt");

    int port = atoi(argv[2]);
    unsigned char* ip=argv[1];



    sock=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    if(sock<0)
    {
        fprintf(stderr,"[-] Socket is not created!\n");
        exit(EXIT_FAILURE);
    }
    printf("[+]Socket is created succesfully!\n");
    server.sin_family=AF_INET;
    server.sin_port=htons(port);
    server.sin_addr.s_addr=inet_addr(ip);

    if(connect(sock,(struct sockaddr*)&server,sizeof(server))<0)
    {
        fprintf(stderr,"[-] Connected is not successfull!\n");
        exit(EXIT_FAILURE);
    }
    printf("[+]Connecting is succesfull!\n");
    system("clear");
    printf("Port: %d\n---------------\n",port);
    printf("Clean the screen: clear\nSave the chat: COMING! \nEXIT: exit\n---------------\n");
    while(1)
    {
        // memory Clear
        memset(message,'\0',sizeof(char)*SIZE);
        memset(sending,'\0',sizeof(char)*SIZE);



        // Send data
        printf("You: ");
        for(int i=0 ; (sending[i]=getchar())!='\n';++i);
        write(sock,sending,sizeof(char)*SIZE);

        if(strncmp(sending,"exit",4)==0)
        {
            printf("Chat is closed...\n");
            goto shutdown;

        }
        else if(strncmp(sending,"clear",5)==0)
            system("clear");

        //read data
        read(sock,message,sizeof(char)*SIZE);
        printf("User: %s\n",message);

        if(c==1)
            saveFile(f,sending,message);



    }
    shutdown:
    printf("If you choose saving the log, [client_log.txt] file Location is:\n");
    system("pwd");
    free(message);
    free(sending);
    shutdown(sock,SHUT_RDWR);

}
