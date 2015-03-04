//
//  main.cpp
//  TCPIPSocketsInC
//
//  Created by guodong on 2/28/15.
//  Copyright (c) 2015 guodong. All rights reserved.
//

#include <iostream>
#include "TCPEchoClient4.h"
#include "TCPEchoServer4.h"
#include "GetAddrInfo.h"

int main(int argc, const char * argv[])
{
#ifdef CLIENT_APP
    Test01_TCPEchoClient(false);
#else
    Test01_TCPEchoServer(false);
#endif
    
    Test02_GetAddrInfo(true);
    return 0;
}
