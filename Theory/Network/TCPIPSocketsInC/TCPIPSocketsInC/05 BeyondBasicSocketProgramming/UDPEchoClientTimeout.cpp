//
//  UDPEchoClientTimeout.cpp
//  TCPIPSocketsInC
//
//  Created by Guo Dong on 3/10/15.
//  Copyright (c) 2015 guodong. All rights reserved.
//
#include <string.h>
#include <netdb.h>
#include <signal.h>
#include <unistd.h>
#include <errno.h>
#include <sys/file.h>

#include "UDPEchoClientTimeout.h"
#include "GUtility.h"
#define MAXSTRINGLENGTH 100
#define TIMEOUT_SECS    2
#define MAXTRIES        5

unsigned int tries = 0;

void CatchAlarm(int ignored)
{
    tries += 1;
    printf("... tries %u\n",tries);
    fflush(stdout);
}

void RunUDPEchoClient(const char* server, const char* echo_str, const char* service)
{
    size_t echo_str_len = strlen(echo_str);
    if (echo_str_len > MAXSTRINGLENGTH)
    {
        GUtility::DieWithUserMessage(echo_str,"too long");
    }
    
    struct addrinfo addr_criteria;
    memset(&addr_criteria, 0, sizeof(addr_criteria));
    addr_criteria.ai_family     = AF_UNSPEC;
    addr_criteria.ai_socktype   = SOCK_DGRAM;
    addr_criteria.ai_protocol   = IPPROTO_UDP;
    
    struct addrinfo* serv_addr;
    int result = getaddrinfo(server, service, &addr_criteria, &serv_addr);
    if (result!=0)
    {
        GUtility::DieWithUserMessage("getaddrinfo() failed", gai_strerror(result));
    }
    int sock = socket(serv_addr->ai_family, serv_addr->ai_socktype, serv_addr->ai_protocol);
    if (sock < 0)
    {
        GUtility::DieWithSystemMessage("socket() failed");
    }
    
    struct sigaction handler;
    handler.sa_handler = CatchAlarm;
    if (sigfillset(&handler.sa_mask)</* DISABLES CODE */ (0))
    {
        GUtility::DieWithSystemMessage("sigfillset() failed");
    }
    handler.sa_flags = 0;
    if (sigaction(SIGALRM, &handler, 0)<0)
    {
        GUtility::DieWithSystemMessage("sigaction() failed");
    }
    ssize_t num_bytes = sendto(sock, echo_str, echo_str_len, 0, serv_addr->ai_addr, serv_addr->ai_addrlen);
    if (num_bytes<0) {
        GUtility::DieWithSystemMessage("sendto() failed");
    }
    else if (num_bytes!=echo_str_len)
    {
        GUtility::DieWithUserMessage("sendto() error","sent unexpected number of bytes");
    }
    
    struct sockaddr_storage from_addr;
    socklen_t from_addr_len = sizeof(from_addr);
    alarm(TIMEOUT_SECS);
    char buffer[MAXSTRINGLENGTH+1];
    while ((num_bytes = recvfrom(sock, buffer, MAXSTRINGLENGTH, 0, (struct sockaddr*)&from_addr, &from_addr_len)) < 0)
    {
        if (errno == EINTR)
        {
            if (tries < MAXTRIES)
            {
                alarm(TIMEOUT_SECS);
                num_bytes = sendto(sock, echo_str, echo_str_len, 0, (struct sockaddr*)serv_addr->ai_addr, serv_addr->ai_addrlen);
                if (num_bytes < 0)
                {
                    GUtility::DieWithSystemMessage("sendto() failed");
                }
                else if (num_bytes!=echo_str_len)
                {
                    GUtility::DieWithUserMessage("sendto() error","sent unexpected number of bytes");
                }
            }
            else
            {
                GUtility::DieWithUserMessage("No Response","unable to communicate with server");
            }
        }
        else
        {
            GUtility::DieWithSystemMessage("recvfrom() failed");
        }
    }
    alarm(0);
    buffer[echo_str_len] = '\0';
    printf("Received: %s\n", buffer);
    
    close(sock);
}

void Test05_UDPEchoClient_Timeout(bool is_run)
{
    if (!is_run)
    {
        return;
    }
    RunUDPEchoClient("127.0.0.1","HelloWorld","7778");
    //RunUDPEchoClient("199.0.0.1","HelloWorld","7777");
}