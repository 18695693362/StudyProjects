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

int main(int argc, const char * argv[]) {
    // insert code here...
    
#ifdef CLIENT_APP
    Test01_TCPEchoClient();
#else
    Test01_TCPEchoServer();
#endif
    return 0;
}
