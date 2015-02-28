//
//  GUtility.cpp
//  TCPIPSocketsInC
//
//  Created by guodong on 2/28/15.
//  Copyright (c) 2015 guodong. All rights reserved.
//

#include "GUtility.h"
#include <string>
#include <stdlib.h>

void GUtility::DieWithUserMessage(const std::string &msg,const std::string& detail)
{
    fputs(msg.c_str(),stderr);
    fputs(": ", stderr);
    fputs(detail.c_str(), stderr);
    fputc('\n', stderr);
    exit(1);
}

void GUtility::DieWithSystemMessage(const std::string &msg)
{
    perror(msg.c_str());
    exit(1);
}

