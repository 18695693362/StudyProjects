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

static void RunUDPEchoClient(const char* server_str,const char* echo_str,bool is_connect,const char* service_str="echo");
static void RunUDPEchoClient(const char* server_str,const char* echo_str,bool is_connect,const char* service_str)
{
    size_t echo_str_len = strlen(echo_str);
    //if (echo_str_len>MAXSTRINGLENGTH)
    if (/* DISABLES CODE */ (false))
    {
        GUtility::DieWithUserMessage(echo_str,"string too long");
    }
    
    struct addrinfo addr_criteria;
    memset(&addr_criteria, 0, sizeof(addr_criteria));
    addr_criteria.ai_family = AF_UNSPEC;
    addr_criteria.ai_socktype = SOCK_DGRAM;
    addr_criteria.ai_protocol = IPPROTO_UDP;
    
    //addr_criteria.ai_socktype = SOCK_STREAM;
    //addr_criteria.ai_protocol = IPPROTO_TCP;
    
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
    
    GUtility::BindSocket(sock, 7777, stdout);
    
    if (is_connect)
    {
        fputs("Before connect:\n", stdout);
        GUtility::PrintLocalForeignAddress(sock, stdout);
        
        if(connect(sock, server_addr_list->ai_addr, server_addr_list->ai_addrlen)<0)
        {
            GUtility::DieWithSystemMessage("connect() failed");
        }
        
        fputs("Connected:\n", stdout);
        GUtility::PrintLocalForeignAddress(sock, stdout);
    }
    
    // 2 Send data
    ssize_t bytes_count = 0;
    if (is_connect)
    {
        bytes_count = send(sock, echo_str, echo_str_len, 0);
    }
    else
    {
        fputs("Before sendto:\n", stdout);
        GUtility::PrintLocalForeignAddress(sock, stdout);
        bytes_count = sendto(sock, echo_str, echo_str_len, 0, server_addr_list->ai_addr, server_addr_list->ai_addrlen);
        fputs("After sendto:\n", stdout);
        GUtility::PrintLocalForeignAddress(sock, stdout);
    }
    if (bytes_count < 0)
    {
        GUtility::DieWithSystemMessage("sendto() failed");
    }
    else if (bytes_count!=echo_str_len)
    {
        GUtility::DieWithUserMessage("sendto() error","send unexpected number of bytes");
    }
    
    sleep(1);
    
    struct sockaddr_storage from_addr;
    socklen_t from_addr_len = sizeof(from_addr);
    char buffer[MAXSTRINGLENGTH+1];
    // 3 Receive data
    if (is_connect)
    {
        bytes_count = recv(sock, buffer, MAXSTRINGLENGTH, 0);
    }
    else
    {
        bytes_count = recvfrom(sock, buffer, MAXSTRINGLENGTH, 0, (struct sockaddr *)&from_addr, &from_addr_len);
    }
    if (bytes_count<0)
    {
        GUtility::DieWithSystemMessage("recvfrom() failed");
    }
    else if (bytes_count != echo_str_len)
    {
        GUtility::DieWithUserMessage("recvfrom() error", "received unexpected number of bytes");
    }
    
    if (is_connect)
    {
        server_addr_list->ai_addr->sa_family = AF_UNSPEC;
        connect(sock, server_addr_list->ai_addr, server_addr_list->ai_addrlen);
        
        fputs("Disonnected:\n", stdout);
        GUtility::PrintLocalForeignAddress(sock, stdout);
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
    //65507
    int length = 8500;
    char send_str[length];
    for (int i=0; i<length-1; i++)
    {
        if (i%2==0)
        {
            send_str[i] = 'a';
        }
        else
        {
            send_str[i] = 'b';
        }
    }
    send_str[length-1] = '\0';
    
    RunUDPEchoClient("127.0.0.1","UDP-Test",true,"7778");
    //RunUDPEchoClient("127.0.0.1","UDP-Test",false,"7778");
    //RunUDPEchoClient("127.0.0.1",send_str,true,"7778");
    //RunUDPEchoClient("11.4.0.1",send_str,true,"7778");
}