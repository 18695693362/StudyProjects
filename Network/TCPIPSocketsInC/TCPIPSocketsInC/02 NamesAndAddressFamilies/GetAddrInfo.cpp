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
        GUtility::PrintSocketAddress(addr->ai_addr, stdout);
        printf(" family=%d ",addr->ai_family);
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
    GetAddrInfo(nullptr, "whois");
    
    exit(0);
}