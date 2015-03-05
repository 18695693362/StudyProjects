//
//  GUtility.cpp
//  TCPIPSocketsInC
//
//  Created by guodong on 2/28/15.
//  Copyright (c) 2015 guodong. All rights reserved.
//

#include "GUtility.h"
#include <string>
#include <stdlib.h>
#include <netdb.h>
#include <arpa/inet.h>

void GUtility::DieWithUserMessage(const std::string &msg,const std::string& detail)
{
    fputs(msg.c_str(),stderr);
    fputs(": ", stderr);
    fputs(detail.c_str(), stderr);
    fputc('\n', stderr);
    exit(1);
}

void GUtility::DieWithSystemMessage(const std::string &msg)
{
    perror(msg.c_str());
    exit(1);
}

void GUtility::PrintSocketAddress(const struct sockaddr* address, FILE* stream)
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

void GUtility::PrintLocalForeignAddress(int socket,FILE* stream)
{
    if (socket<0)
    {
        DieWithUserMessage("PrintLocalForeignAddress() failed","invalid socket");
    }
    
    // print client address
    sockaddr_storage temp_addr;
    socklen_t   temp_addr_len = sizeof(temp_addr);
    memset(&temp_addr, 0, sizeof(temp_addr));
    getsockname(socket, (struct sockaddr *)&temp_addr, &temp_addr_len);
    fputs("==local info==\n",stream);
    GUtility::PrintSocketAddress((struct sockaddr *)&temp_addr, stream);
    fputc('\n', stream);
    
    // print foreign address
    getpeername(socket, (struct sockaddr *)&temp_addr, &temp_addr_len);
    fputs("==server info==\n",stream);
    GUtility::PrintSocketAddress((struct sockaddr *)&temp_addr, stream);
    fputc('\n', stream);
}

void GUtility::BindSocket(int socket,unsigned int port,FILE* stream)
{
    sockaddr_storage temp_addr;
    socklen_t   temp_addr_len = sizeof(temp_addr);
    memset(&temp_addr, 0, sizeof(temp_addr));
    getsockname(socket, (struct sockaddr *)&temp_addr, &temp_addr_len);
    switch (temp_addr.ss_family)
    {
        case AF_INET:
        {
            struct sockaddr_in* address = (struct sockaddr_in*)&temp_addr;
            address->sin_port = htons(port);
            break;
        }
        case AF_INET6:
        {
            struct sockaddr_in6* address = (struct sockaddr_in6*)&temp_addr;
            address->sin6_port = htons(port);
            break;
        }
        default:
            fputs("[unknown type]", stream);
            return;
    }
    bind(socket, (struct sockaddr *)&temp_addr, temp_addr_len);
}

template<typename SrcDataType>
void GUtility::PrintWithBinaryFormat(FILE* stream,SrcDataType data,size_t bytes_len)
{
    if (bytes_len==0)
    {
        bytes_len = sizeof(SrcDataType);
    }
    for (size_t i=0; i<bytes_len; i++)
    {
        //todo
    }
}


















