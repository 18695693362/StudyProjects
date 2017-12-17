//
//  TCPServerUtility.h
//  TCPIPSocketsInC
//
//  Created by guodong on 3/4/15.
//  Copyright (c) 2015 guodong. All rights reserved.
//

#ifndef __TCPIPSocketsInC__TCPServerUtility__
#define __TCPIPSocketsInC__TCPServerUtility__

#include <stdio.h>

int SetupTCPServerSocket(const char* server);
int AcceptTCPConnection(int server_sock);

#endif /* defined(__TCPIPSocketsInC__TCPServerUtility__) */
