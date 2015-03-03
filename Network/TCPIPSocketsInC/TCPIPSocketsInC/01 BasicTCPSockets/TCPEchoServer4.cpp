//
//  TCPEchoServer4.cpp
//  TCPIPSocketsInC
//
//  Created by Guo Dong on 3/1/15.
//  Copyright (c) 2015 guodong. All rights reserved.
//

#include "TCPEchoServer4.h"
#include <string>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "GUtility.h"

#define INET_ADDRSTRLEN 100
#define BUFFSIZE 128

//maximum outstanding connection requests
static const int MAXPENDING = 5;

void HandleTCPClient(int client_socket)
{
    char buffer[BUFFSIZE];
    
    // print client address
    sockaddr_in temp_addr;
    socklen_t   temp_addr_len = sizeof(temp_addr);
    memset(&temp_addr, 0, sizeof(temp_addr));
    getsockname(client_socket, (struct sockaddr *)&temp_addr, &temp_addr_len);
    char temp_addr_str[INET_ADDRSTRLEN];
    if ( inet_ntop(AF_INET, &temp_addr.sin_addr.s_addr, temp_addr_str,sizeof(temp_addr_str)) !=NULL )
    {
        printf("==local  info %s/%d\n", temp_addr_str, ntohs(temp_addr.sin_port));
    }
    else
    {
        puts("==unable to get client address");
    }
    // print server address
    getpeername(client_socket, (struct sockaddr *)&temp_addr, &temp_addr_len);
    if ( inet_ntop(AF_INET, &temp_addr.sin_addr.s_addr, temp_addr_str,sizeof(temp_addr_str)) !=NULL )
    {
        printf("==server info %s/%d\n", temp_addr_str, ntohs(temp_addr.sin_port));
    }
    else
    {
        puts("==unable to get server address");
    }
    
    ssize_t num_bytes_recv = recv(client_socket, buffer, BUFFSIZE, 0);
    if (num_bytes_recv<0) {
        GUtility::DieWithSystemMessage("recv() failed");
    }
    
    while (num_bytes_recv>0)
    {
        ssize_t num_bytes_send = send(client_socket, buffer, num_bytes_recv, 0);
        if (num_bytes_send < 0)
        {
            GUtility::DieWithSystemMessage("send() failed");
        }
        else if(num_bytes_send!=num_bytes_recv)
        {
            GUtility::DieWithUserMessage("send()", "sent unexpected number of bytes");
        }
        
        num_bytes_recv = recv(client_socket, buffer, BUFFSIZE, 0);
        if (num_bytes_recv<0)
        {
            GUtility::DieWithSystemMessage("recv() failed");
        }
    }
    
    close(client_socket);
}

void RunTCPEchoServer(const char* port="7777");
void RunTCPEchoServer(const char* port)
{
    in_port_t server_port = atoi(port);
    
    // 1 Create socket
    int server_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (server_port<0)
    {
        GUtility::DieWithSystemMessage("socket() failed");
    }
    
    // 2 Prepare server address
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(server_port);
    
    // 3 Bind to the local address
    if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)))
    {
        GUtility::DieWithSystemMessage("bind() failed");
    }
    
    // 4 Mark socket to listen incomming connections
    if (listen(server_socket, MAXPENDING))
    {
        GUtility::DieWithSystemMessage("listen() failed");
    }
    
    // 5 Process TCP client
    while (true)
    {
        struct sockaddr_in client_addr;
        socklen_t client_addr_len = sizeof(client_addr);
        
        // 5-1 wait for a client to connect
        int client_socket = accept(server_socket, (struct sockaddr*)&client_addr, &client_addr_len);
        if (client_socket<0)
        {
            GUtility::DieWithSystemMessage("accept() failed");
        }
        
        // 5-2 process client
        char client_name[INET_ADDRSTRLEN];
        if ( inet_ntop(AF_INET, &client_addr.sin_addr.s_addr, client_name,sizeof(client_name)) !=NULL )
        {
            printf("Handling client %s/%d\n", client_name, ntohs(client_addr.sin_port));
        }
        else
        {
            puts("Unable to get client address");
        }
        
        HandleTCPClient(client_socket);
    }
}

void Test01_TCPEchoServer()
{
    RunTCPEchoServer();
}