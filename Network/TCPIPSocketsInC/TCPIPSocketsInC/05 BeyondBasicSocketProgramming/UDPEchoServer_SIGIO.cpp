//
//  UDPEchoServer_SIGIO.cpp
//  TCPIPSocketsInC
//
//  Created by Guo Dong on 3/9/15.
//  Copyright (c) 2015 guodong. All rights reserved.
//
#include <netdb.h>
#include <string.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/file.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>

#include "UDPEchoServer_SIGIO.h"
#include "GUtility.h"
#include "GetAddrInfo.h"

#define MAXSTRINGLENGTH 100
static int serv_sock;

void UseIdleTime()
{
    puts(".");
    sleep(3);
}

void SIGIOHandler(int signal_type)
{
    ssize_t num_bytes_recv;
    do{
        struct sockaddr_storage client_addr;
        socklen_t client_addr_len = sizeof(client_addr);
        char buffer[MAXSTRINGLENGTH];
        num_bytes_recv = recvfrom(serv_sock, buffer, MAXSTRINGLENGTH, 0, (struct sockaddr *)&client_addr, &client_addr_len);
        if (num_bytes_recv<0)
        {
            if (errno != EWOULDBLOCK)
            {
                GUtility::DieWithSystemMessage("recvfrom() failed");
            }
        }
        else
        {
            fprintf(stdout, "Handling client ");
            GUtility::PrintSocketAddress((struct sockaddr*)&client_addr, stdout);
            fputc('\n', stdout);
            
            ssize_t num_bytes_send = sendto(serv_sock, buffer, num_bytes_recv, 0,( struct sockaddr *)&client_addr, client_addr_len);
            if (num_bytes_send < 0)
            {
                GUtility::DieWithSystemMessage("sendto() failed");
            }
            else if (num_bytes_send != num_bytes_recv)
            {
                GUtility::DieWithUserMessage("sendto()","sent unexpected number of bytes");
            }
            fprintf(stdout, "Handling client ---\n");
        }
    }while (num_bytes_recv >= 0);
}

static void RunUDPEchoServer(bool is_connect,const char* service_str="echo");
static void RunUDPEchoServer(bool is_connect,const char* service_str)
{
    struct addrinfo addr_criteria;
    memset(&addr_criteria,0,sizeof(addr_criteria));
    addr_criteria.ai_family = AF_UNSPEC;
    addr_criteria.ai_flags  = AI_PASSIVE;
    addr_criteria.ai_socktype = SOCK_DGRAM;
    addr_criteria.ai_protocol = IPPROTO_UDP;
    
    struct addrinfo* serv_addr;
    int result = getaddrinfo(nullptr, service_str, &addr_criteria, &serv_addr);
    if (result != 0)
    {
        GUtility::DieWithUserMessage("getaddrinfo() failed", gai_strerror(result));
    }
    
    serv_sock = socket(serv_addr->ai_family, serv_addr->ai_socktype, serv_addr->ai_protocol);
    if (serv_sock<0)
    {
        GUtility::DieWithSystemMessage("socket() failed");
    }
    if (bind(serv_sock, serv_addr->ai_addr, serv_addr->ai_addrlen)<0)
    {
        GUtility::DieWithSystemMessage("bind() failed");
    }
    
    freeaddrinfo(serv_addr);
    struct sigaction handler;
    handler.sa_handler = SIGIOHandler;
    if (sigfillset(&handler.sa_mask) < /* DISABLES CODE */ (0))
    {
        GUtility::DieWithSystemMessage("sigfillset() failed");
    }
    handler.sa_flags = 0;
    
    if (sigaction(SIGIO, &handler, 0)<0)
    {
        GUtility::DieWithSystemMessage("sigaction() failed for SIGIO");
    }
    
    if (fcntl(serv_sock, F_SETOWN, getpid()) < 0)
    {
        GUtility::DieWithSystemMessage("Unable to set process owner to us");
    }
    
    if (fcntl(serv_sock, F_SETFL, O_NONBLOCK|FASYNC) < 0)
    {
        GUtility::DieWithSystemMessage("Unable to put client sock into non-blocking/async mode");
    }
    
    while (true)
    {
        UseIdleTime();
    }
}

void Test05_UDPEchoServer_SIGIO(bool is_run)
{
    if (!is_run)
    {
        return;
    }
    RunUDPEchoServer(false,"7778");
}