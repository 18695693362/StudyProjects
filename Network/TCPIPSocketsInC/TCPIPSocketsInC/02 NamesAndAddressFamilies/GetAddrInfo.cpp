//
//  GetAddrInfo.cpp
//  TCPIPSocketsInC
//
//  Created by guodong on 3/3/15.
//  Copyright (c) 2015 guodong. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "GUtility.h"
#include "GetAddrInfo.h"

void PrintSocketAddress(const struct sockaddr* address, FILE* stream)
{
    if (address == nullptr || stream == nullptr)
    {
        return;
    }
    
    void* numeric_addr;
    char addr_buffer[INET6_ADDRSTRLEN];
    in_port_t port;
    
    switch (address->sa_family)
    {
        case AF_INET:
            numeric_addr = &((struct sockaddr_in*) address)->sin_addr;
            port = ntohs(((struct sockaddr_in*) address)->sin_port);
            break;
        case AF_INET6:
            numeric_addr = &((struct sockaddr_in6*) address)->sin6_addr;
            port = ntohs(((struct sockaddr_in6*) address)->sin6_port);
        default:
            fputs("[unknown type]", stream);
            return;
    }
    
    if (inet_ntop(address->sa_family, numeric_addr, addr_buffer, sizeof(addr_buffer))==nullptr)
    {
        fputs("[invalid address]", stream);
    }
    else
    {
        fprintf(stream, "%s", addr_buffer);
        if (port != 0)
        {
            fprintf(stream, "-%u", port);
        }
    }
}

void GetAddrInfo(const char* addr_str,const char* port_str)
{
    struct addrinfo temp_addrinfo;
    memset(&temp_addrinfo, 0, sizeof(temp_addrinfo));
    temp_addrinfo.ai_family = AF_UNSPEC;
    temp_addrinfo.ai_socktype = SOCK_STREAM;
    temp_addrinfo.ai_protocol = IPPROTO_TCP;
    
    struct addrinfo* addrlist;
    int result = getaddrinfo(addr_str, port_str, &temp_addrinfo, &addrlist);
    if(result != 0)
    {
        GUtility::DieWithUserMessage("getaddrinfo() failed", gai_strerror(result));
    }
    
    for (struct addrinfo* addr = addrlist; addr!=nullptr; addr=addr->ai_next)
    {
        PrintSocketAddress(addr->ai_addr, stdout);
        fputc('\n', stdout);
    }
    fputc('\n', stdout);
    
    freeaddrinfo(addrlist);
}

void Test02_GetAddrInfo(bool is_run)
{
    if (!is_run)
    {
        return;
    }
    GetAddrInfo("www.baidu.com", "80");
    GetAddrInfo("www.google.com", "80");
    GetAddrInfo("www.qq.com", "whois");
    
    exit(0);
}