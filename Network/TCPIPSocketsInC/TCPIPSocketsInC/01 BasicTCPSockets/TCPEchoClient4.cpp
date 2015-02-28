//
//  TCPEchoClient4.cpp
//  TCPIPSocketsInC
//
//  Created by guodong on 2/28/15.
//  Copyright (c) 2015 guodong. All rights reserved.
//

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "TCPEchoClient4.h"
#include "GUtility.h"

void RunTCPEchoClient(const char* server_ip, const char* echo_str, const char* port="7777");
void RunTCPEchoClient(const char* server_ip, const char* echo_str, const char* port)
{
//    in_port_t
}

void Test01_TCPEchoClient()
{
    RunTCPEchoClient("172.16.3.71", "Test", "4000");
}