//
//  GUtility.h
//  TCPIPSocketsInC
//
//  Created by guodong on 2/28/15.
//  Copyright (c) 2015 guodong. All rights reserved.
//

#ifndef __TCPIPSocketsInC__GUtility__
#define __TCPIPSocketsInC__GUtility__

#include <string>

class GUtility
{
public:
    static void DieWithUserMessage(const std::string& msg,const std::string& detail="");
    static void DieWithSystemMessage(const std::string&msg);
};

#endif /* defined(__TCPIPSocketsInC__GUtility__) */
