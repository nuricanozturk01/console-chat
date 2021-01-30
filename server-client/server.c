#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "serverClient.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#define SIZE 2048
#define MAX 5

int main(int argc,char** argv)
{

    int sockfd,newsock,c;


    struct sockaddr_in server;
    struct sockaddr_in client;


    char* message=malloc(sizeof(char)*SIZE);
    char* sending=malloc(sizeof(char)*SIZE);


    if(argc<2)
    {
        fprintf(stderr,"Usage: %s <portNumber>\n",argv[0]);
        exit(EXIT_FAILURE);
    }
    // FILE OPERATIONS
    FILE* f=fopen("server_log.txt","a");

    if(!f)
    {
        perror("[-]File is not created....\n");
        printf("[+]File is created successfully!\n");
    }

    //log screen
    printf("Dou you want to log?\n1-Yes\n2-No\n");
    scanf("%d",&c);

    if(c==2)
        remove("server_log.txt");

    //ip and port parameter
    int port=atoi(argv[1]);



    sockfd=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    if(sockfd<0)
    {
        fprintf(stderr,"[-] Socket is not created!\n");
        exit(EXIT_FAILURE);
    }
    printf("[+]Socket is created successfully!\n");




    //define necessary structs
    server.sin_family=AF_INET;
    server.sin_port=htons(port);
    server.sin_addr.s_addr=htonl(INADDR_ANY);

    if(bind(sockfd,(struct sockaddr*)&server,sizeof(server))<0)
    {
        fprintf(stderr,"[-]Binding is not successfull!\n");
        exit(EXIT_FAILURE);
    }
    printf("[+]Binding is successfull!\n");


    if(listen(sockfd,MAX)<0)
    {
        fprintf(stderr,"[-]Listened is not successfull\n");
        exit(EXIT_FAILURE);
    }
    printf("[+]Listening is successfull\n");


    int sSize=sizeof(client);

    newsock=accept(sockfd,(struct sockaddr*)&client,&sSize);
    if(newsock<0)
    {
        fprintf(stderr,"[-]Accept is not successfull\n");
        exit(EXIT_FAILURE);
    }


    printf("[+]Accept is successfull\n");
    system("clear");
    printf("Port: %d\n---------------\n",port);
    printf("Clean the screen: clear\nSave the chat: COMING! \nEXIT: exit\n---------------\n");

    
    while(1)
    {
        //clear memory
        memset(message,'\0',sizeof(char)*SIZE);
        memset(sending,'\0',sizeof(char)*SIZE);

        //read data
        read(newsock,message,sizeof(char)*SIZE);
        printf("User: %s\n",message);


        // send data
        printf("You: ");
        for(int i=0 ; (sending[i]=getchar())!='\n';++i);
        write(newsock,sending,sizeof(char)*SIZE);



        if(strncmp(sending,"exit",4)==0)
        {

            printf("Chat is closed...\n");
            goto shutdown;
        }
        else if(strncmp(sending,"clear",5)==0)
            system("clear");


        if(c==1)
            saveFile(f,sending,message);


    }

    shutdown:
    fclose(f);
    printf("If you choose saving the log, [server_log.txt]  file Location is:\n");
    system("pwd");
    free(message);
    free(sending);
    shutdown(newsock,SHUT_RDWR);
    shutdown(sockfd,SHUT_RDWR);



}
