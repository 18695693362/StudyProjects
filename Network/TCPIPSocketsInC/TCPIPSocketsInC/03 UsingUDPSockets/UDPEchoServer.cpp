//
//  UDPEchoServer.cpp
//  TCPIPSocketsInC
//
//  Created by guodong on 3/4/15.
//  Copyright (c) 2015 guodong. All rights reserved.
//

#include <string.h>
#include <stdio.h>
#include <netdb.h>
#include "UDPEchoServer.h"
#include "GUtility.h"
#include "GetAddrInfo.h"
#define MAXSTRINGLENGTH 100

static void RunUDPEchoServer(const char* service_str="echo");
static void RunUDPEchoServer(const char* service_str)
{
    struct addrinfo addr_criteria;
    memset(&addr_criteria, 0, sizeof(addr_criteria));
    addr_criteria.ai_family = AF_UNSPEC;
    addr_criteria.ai_flags  = AI_PASSIVE;
    addr_criteria.ai_socktype = SOCK_DGRAM;
    addr_criteria.ai_protocol = IPPROTO_UDP;
    
    struct addrinfo* server_addr_list;
    int result = getaddrinfo(nullptr, service_str, &addr_criteria, &server_addr_list);
    if (result!=0)
    {
        GUtility::DieWithUserMessage("getaddrinfo failed",gai_strerror(result));
    }
    
    // Create Socket
    int sock = socket(server_addr_list->ai_family, server_addr_list->ai_socktype, server_addr_list->ai_protocol);
    if (sock<0)
    {
        GUtility::DieWithSystemMessage("socket() failed");
    }
    
    // Bind Socket
    if (bind(sock, server_addr_list->ai_addr, server_addr_list->ai_addrlen)<0)
    {
        GUtility::DieWithSystemMessage("bind() failed");
    }
    
    freeaddrinfo(server_addr_list);
    
    while (true)
    {
        struct sockaddr_storage client_addr;
        socklen_t client_addr_len = sizeof(client_addr);
        char buffer[MAXSTRINGLENGTH];
        ssize_t bytes_count_recv = recvfrom(sock, buffer, MAXSTRINGLENGTH, 0, (struct sockaddr *)&client_addr, &client_addr_len);
        if (bytes_count_recv < 0)
        {
            GUtility::DieWithSystemMessage("recvfrom() failed");
        }
        
        fputs("Handling client ", stdout);
        PrintSocketAddress((struct sockaddr *)&client_addr, stdout);
        fputc('\n', stdout);
        
        ssize_t bytes_count_send = sendto(sock, buffer, bytes_count_recv, 0, (struct sockaddr *)&client_addr, client_addr_len);
        if (bytes_count_send < 0)
        {
            GUtility::DieWithSystemMessage("sendto() failed");
        }
        else if (bytes_count_send!=bytes_count_recv)
        {
            GUtility::DieWithUserMessage("sendto()", "send unexpected number of bytes");
        }
    }
}

void Test03_UDPEchoServer(bool is_run)
{
    if (!is_run)
    {
        return;
    }
    
    RunUDPEchoServer("7778");
}