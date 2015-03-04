//
//  GetAddrInfo.h
//  TCPIPSocketsInC
//
//  Created by guodong on 3/3/15.
//  Copyright (c) 2015 guodong. All rights reserved.
//

#ifndef TCPIPSocketsInC_GetAddrInfo_h
#define TCPIPSocketsInC_GetAddrInfo_h

#include <stdio.h>

void PrintSocketAddress(const struct sockaddr* address, FILE* stream);
void Test02_GetAddrInfo(bool is_run);

#endif
