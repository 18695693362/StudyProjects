//
//  TCPEchoClient4.cpp
//  TCPIPSocketsInC
//
//  Created by guodong on 2/28/15.
//  Copyright (c) 2015 guodong. All rights reserved.
//

#include <string>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "TCPEchoClient4.h"
#include "GUtility.h"

#define BUFFSIZE 128

void RunTCPEchoClient(const char* server_ip, const char* echo_str, const char* port="7777");
void RunTCPEchoClient(const char* server_ip, const char* echo_str, const char* port)
{
    in_port_t server_port = atoi(port);
    
    // 1 Create socket
    int sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock<0)
    {
        GUtility::DieWithSystemMessage("socket() failed");
    }
    
    // 2 Create Server Address
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    
    // 3 Convert Server Address
    int result = inet_pton(AF_INET, server_ip, &server_addr.sin_addr.s_addr);
    if (result==0)
    {
        GUtility::DieWithUserMessage("inet_pton() failed", "invalid address string");
    }
    else if(result<0)
    {
        GUtility::DieWithSystemMessage("inet_pton() failed");
    }
    server_addr.sin_port = htons(server_port);
    
    // bind client socket
    struct sockaddr_in client_addr;
    memset(&client_addr, 0, sizeof(client_addr));
    client_addr.sin_family = AF_INET;
    client_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    client_addr.sin_port = htons(4678);
    if (bind(sock, (struct sockaddr *)&client_addr, sizeof(client_addr)))
    {
        GUtility::DieWithSystemMessage("bind() failed");
    }
    
    // 4 Establish the connection to the echo server
    if (connect(sock, (sockaddr*)&server_addr, sizeof(server_addr))<0)
    {
        GUtility::DieWithSystemMessage("connect() failed");
    }
    
    // 4-1 print local address
    sockaddr_in temp_addr;
    socklen_t   temp_addr_len = sizeof(temp_addr);
    memset(&temp_addr, 0, sizeof(temp_addr));
    getsockname(sock, (struct sockaddr *)&temp_addr, &temp_addr_len);
    char temp_addr_str[INET_ADDRSTRLEN];
    if ( inet_ntop(AF_INET, &temp_addr.sin_addr.s_addr, temp_addr_str,sizeof(temp_addr_str)) !=NULL )
    {
        printf("local  info %s/%d\n", temp_addr_str, ntohs(temp_addr.sin_port));
    }
    else
    {
        puts("Unable to get client address");
    }
    
    // 4-2 print server address
    getpeername(sock, (struct sockaddr *)&temp_addr, &temp_addr_len);
    if ( inet_ntop(AF_INET, &temp_addr.sin_addr.s_addr, temp_addr_str,sizeof(temp_addr_str)) !=NULL )
    {
        printf("server info %s/%d\n", temp_addr_str, ntohs(temp_addr.sin_port));
    }
    else
    {
        puts("Unable to get server address");
    }
    
    // 5 Send string to server
    size_t echo_str_len = strlen(echo_str);
    ssize_t num_bytes = send(sock, echo_str, echo_str_len, 0);
    if (num_bytes<0)
    {
        GUtility::DieWithSystemMessage("send() failed");
    }
    else if (num_bytes!=echo_str_len)
    {
        GUtility::DieWithUserMessage("send()", "send unexpected number of bytes");
    }
    
    // 6 Receive the same string from server
    unsigned int total_bytes_recv = 0;
    fputs("Received: ", stdout);
    while (total_bytes_recv<echo_str_len)
    {
        char buffer[BUFFSIZE];
        num_bytes = recv(sock, buffer, BUFFSIZE-1, 0);
        if (num_bytes<0)
        {
            GUtility::DieWithSystemMessage("recv() failed!");
        }
        else if (num_bytes == 0)
        {
            GUtility::DieWithUserMessage("recv()", "connection closed prematruely");
        }
        
        total_bytes_recv += num_bytes;
        buffer[num_bytes] = '\0';
        fputs(buffer, stdout);
    }
    
    fputc('\n', stdout);
    
    // 7 Close socket
    close(sock);
}

void Test01_TCPEchoClient(bool is_run)
{
    if (!is_run)
    {
        return;
    }
    //RunTCPEchoClient("172.16.3.71", "Test", "4000");
    RunTCPEchoClient("127.0.0.1", "Test");
}