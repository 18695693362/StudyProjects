//
//  TCPEchoServer.cpp
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

#include "TCPEchoServer.h"
#include "TCPServerUtility.h"
#include "GetAddrInfo.h"
#include "GUtility.h"

#define BUFFSIZE 128

static void HandleTCPClient(int client_socket)
{
    char buffer[BUFFSIZE];
    ssize_t num_bytes_recv = recv(client_socket, buffer, BUFFSIZE, 0);
    if (num_bytes_recv<0) {
        GUtility::DieWithSystemMessage("recv() failed");
    }
    
    // print client address
    sockaddr_storage temp_addr;
    socklen_t   temp_addr_len = sizeof(temp_addr);
    memset(&temp_addr, 0, sizeof(temp_addr));
    getsockname(client_socket, (struct sockaddr *)&temp_addr, &temp_addr_len);
    puts("==local info==");
    GUtility::PrintSocketAddress((struct sockaddr *)&temp_addr, stdout);
    putc('\n', stdout);

    // print server address
    getpeername(client_socket, (struct sockaddr *)&temp_addr, &temp_addr_len);
    puts("==server info==");
    GUtility::PrintSocketAddress((struct sockaddr *)&temp_addr, stdout);
    putc('\n', stdout);
    
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

static void RunTCPEchoServer(const char* port="7777");
static void RunTCPEchoServer(const char* port)
{
    int server_socket = SetupTCPServerSocket(port);
    if (server_socket<0)
    {
        GUtility::DieWithUserMessage("SetupTCPServerSocket() failed",port);
    }
    
    while (true)
    {
        int client_socket = AcceptTCPConnection(server_socket);
        HandleTCPClient(client_socket);
    }
}

void Test02_TCPEchoServer(bool is_run)
{
    if (!is_run)
    {
        return;
    }
    RunTCPEchoServer();
}