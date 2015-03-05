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
#include "TCPEchoClient.h"
#include "TCPEchoServer.h"
#include "UDPEchoClient.h"
#include "UDPEchoServer.h"
#include "TestSizes.h"

int main(int argc, const char * argv[])
{
#ifdef CLIENT_APP
    Test01_TCPEchoClient(false);
    Test02_TCPEchoClient(false);
    Test03_UDPEchoClient(false);
#else
    Test01_TCPEchoServer(false);
    Test02_TCPEchoServer(false);
    Test03_UDPEchoServer(false);
#endif
    
    Test02_GetAddrInfo(false);
    Test04_TestSizes(true);
    return 0;
}
