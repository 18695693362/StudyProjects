//
//  TCPClientUtility.cpp
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

#include "TCPClientUtility.h"
#include "GUtility.h"

int SetupTCPClientSocket(const char* host, const char* service)
{
    struct addrinfo addr_criteria;
    memset(&addr_criteria, 0, sizeof(addr_criteria));
    addr_criteria.ai_family = AF_UNSPEC;
    addr_criteria.ai_socktype = SOCK_STREAM;
    addr_criteria.ai_protocol = IPPROTO_TCP;
    
    struct addrinfo* server_addr;
    int result = getaddrinfo(host, service, &addr_criteria, &server_addr);
    if (result!=0)
    {
        GUtility::DieWithUserMessage("getaddrinfo() failed", gai_strerror(result));
    }
    
    int sock = -1;
    for (struct addrinfo* addr=server_addr; addr!=nullptr; addr=addr->ai_next)
    {
        sock = socket(addr->ai_family, addr->ai_socktype, addr->ai_protocol);
        if (sock < 0)
        {
            continue;
        }
        
        if (connect(sock, addr->ai_addr, addr->ai_addrlen) == 0)
        {
            break;
        }
        
        close(sock);
        
        sock = -1;
    }
    
    freeaddrinfo(server_addr);
    return sock;
}














