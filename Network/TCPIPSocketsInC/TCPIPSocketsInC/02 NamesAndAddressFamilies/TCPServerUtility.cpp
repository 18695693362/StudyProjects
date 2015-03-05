//
//  TCPServerUtility.cpp
//  TCPIPSocketsInC
//
//  Created by guodong on 3/4/15.
//  Copyright (c) 2015 guodong. All rights reserved.
//

#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

#include "GetAddrInfo.h"
#include "TCPServerUtility.h"
#include "GUtility.h"
static const int MAXPENDING = 5;

int SetupTCPServerSocket(const char* service)
{
    struct addrinfo addr_criteria;
    memset(&addr_criteria, 0, sizeof(addr_criteria));
    addr_criteria.ai_family = AF_UNSPEC;
    addr_criteria.ai_flags  = AI_PASSIVE;
    addr_criteria.ai_socktype = SOCK_STREAM;
    addr_criteria.ai_protocol = IPPROTO_TCP;
    
    struct addrinfo* server_addr_list;
    int result = getaddrinfo(nullptr, service, &addr_criteria, &server_addr_list);
    if (result!=0)
    {
        GUtility::DieWithUserMessage("getaddrinfo() failed", gai_strerror(result));
    }
    
    int server_sock = -1;
    for (struct addrinfo* addr=server_addr_list; addr!=nullptr; addr=addr->ai_next)
    {
        server_sock = socket(addr->ai_family, addr->ai_socktype, addr->ai_protocol);
        
        if (server_sock<0)
        {
            continue;
        }
        
        if ((bind(server_sock, addr->ai_addr, addr->ai_addrlen) == 0) && (listen(server_sock, MAXPENDING)==0))
        {
            struct sockaddr_storage local_addr;
            socklen_t addr_size = sizeof(local_addr);
            if (getsockname(server_sock, (struct sockaddr *)&local_addr, &addr_size)<0)
            {
                GUtility::DieWithSystemMessage("getsockname() failed");
            }
            fputs("Binding to ", stdout);
            GUtility::PrintSocketAddress((struct sockaddr*)&local_addr, stdout);
            fputc('\n', stdout);
            break;
        }
        
        close(server_sock);
        server_sock = -1;
    }
    
    freeaddrinfo(server_addr_list);
    return server_sock;
}

int AcceptTCPConnection(int server_sock)
{
    struct sockaddr_storage client_addr;
    socklen_t client_addr_len = sizeof(client_addr);
    
    int client_sock = accept(server_sock, (struct sockaddr*)&client_addr, &client_addr_len);
    if (client_sock<0)
    {
        GUtility::DieWithSystemMessage("accept() failed");
    }
    
    fputs("Handling client ", stdout);
    GUtility::PrintSocketAddress((struct sockaddr *)&client_addr, stdout);
    fputc('\n', stdout);
    
    return client_sock;
}












