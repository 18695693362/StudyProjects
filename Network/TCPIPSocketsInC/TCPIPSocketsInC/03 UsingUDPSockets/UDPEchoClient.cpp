//
//  UDPEchoClient.cpp
//  TCPIPSocketsInC
//
//  Created by guodong on 3/4/15.
//  Copyright (c) 2015 guodong. All rights reserved.
//

#include <string.h>
#include <netdb.h>
#include <unistd.h>
#include "UDPEchoClient.h"
#include "GUtility.h"
#define MAXSTRINGLENGTH 100

static void RunUDPEchoClient(const char* server_str,const char* echo_str,const char* service_str="echo");
static void RunUDPEchoClient(const char* server_str,const char* echo_str,const char* service_str)
{
    size_t echo_str_len = strlen(echo_str);
    if (echo_str_len>MAXSTRINGLENGTH)
    {
        GUtility::DieWithUserMessage(echo_str,"string too long");
    }
    
    struct addrinfo addr_criteria;
    memset(&addr_criteria, 0, sizeof(addr_criteria));
    addr_criteria.ai_family = AF_UNSPEC;
    addr_criteria.ai_socktype = SOCK_DGRAM;
    addr_criteria.ai_protocol = IPPROTO_UDP;
    
    struct addrinfo* server_addr_list;
    int result = getaddrinfo(server_str, service_str, &addr_criteria, &server_addr_list);
    if (result!=0)
    {
        GUtility::DieWithUserMessage("getaddrinfo() failed", gai_strerror(result));
    }
    
    // 1 Create socket
    int sock = socket(server_addr_list->ai_family, server_addr_list->ai_socktype, server_addr_list->ai_protocol);
    if (sock<0)
    {
        GUtility::DieWithSystemMessage("socket() failed");
    }
    
    // 2 Send data
    ssize_t bytes_count = sendto(sock, echo_str, echo_str_len, 0, server_addr_list->ai_addr, server_addr_list->ai_addrlen);
    if (bytes_count < 0)
    {
        GUtility::DieWithSystemMessage("sendto() failed");
    }
    else if (bytes_count!=echo_str_len)
    {
        GUtility::DieWithUserMessage("sendto() error","send unexpected number of bytes");
    }
    
    struct sockaddr_storage from_addr;
    socklen_t from_addr_len = sizeof(from_addr);
    char buffer[MAXSTRINGLENGTH+1];
    // 3 Receive data
    bytes_count = recvfrom(sock, buffer, MAXSTRINGLENGTH, 0, (struct sockaddr *)&from_addr, &from_addr_len);
    if (bytes_count<0)
    {
        GUtility::DieWithSystemMessage("recvfrom() failed");
    }
    else if (bytes_count != echo_str_len)
    {
        GUtility::DieWithUserMessage("recvfrom() error", "received unexpected number of bytes");
    }
    
    freeaddrinfo(server_addr_list);
    
    buffer[echo_str_len] = '\0';
    printf("Received: %s\n", buffer);
    close(sock);
}

void Test03_UDPEchoClient(bool is_run)
{
    if (!is_run)
    {
        return;
    }
    
    RunUDPEchoClient("127.0.0.1","UDP-Test","7778");
}