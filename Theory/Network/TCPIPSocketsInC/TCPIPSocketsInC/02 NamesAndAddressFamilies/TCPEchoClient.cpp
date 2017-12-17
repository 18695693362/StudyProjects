//
//  TCPEchoClient.cpp
//  TCPIPSocketsInC
//
//  Created by guodong on 3/4/15.
//  Copyright (c) 2015 guodong. All rights reserved.
//

#include <string>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "TCPEchoClient.h"
#include "TCPClientUtility.h"
#include "GUtility.h"

#define BUFFSIZE 128

static void RunTCPEchoClient(const char* server_ip, const char* echo_str, const char* port="7777");
static void RunTCPEchoClient(const char* server_ip, const char* echo_str, const char* port)
{
    // 1 Create socket
    //int sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    int sock = SetupTCPClientSocket(server_ip, port);
    if (sock<0)
    {
        GUtility::DieWithUserMessage("SetupTCPClientSocket() failed", "unable to connect");
    }
    
    size_t echo_str_len = strlen(echo_str);
    ssize_t bytes_count = send(sock, echo_str, echo_str_len, 0);
    if (bytes_count<0)
    {
        GUtility::DieWithSystemMessage("send() failed");
    }
    else if (bytes_count!=echo_str_len)
    {
        GUtility::DieWithUserMessage("send()", "sent unexpected number of bytes");
    }
    
    unsigned int total_bytes_recv = 0;
    fputs("Received: ", stdout);
    while (total_bytes_recv<echo_str_len)
    {
        char buffer[BUFFSIZE];
        bytes_count = recv(sock, buffer, BUFFSIZE-1, 0);
        if (bytes_count<0)
        {
            GUtility::DieWithSystemMessage("recv() failed");
        }
        else if (bytes_count==0)
        {
            GUtility::DieWithUserMessage("recv()", "connection closed prematurely");
        }
        
        total_bytes_recv += bytes_count;
        buffer[bytes_count] = '\0';
        fputs(buffer, stdout);
    }
    
    fputc('\n', stdout);
    close(sock);
}

void Test02_TCPEchoClient(bool is_run)
{
    if (!is_run)
    {
        return;
    }
    //RunTCPEchoClient("172.16.3.71", "Test", "4000");
    RunTCPEchoClient("127.0.0.1", "Test");
}
