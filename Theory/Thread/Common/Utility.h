//
//  Utility.h
//  ThreadTutorial
//
//  Created by guodong on 4/2/14.
//  Copyright (c) 2014 guodong. All rights reserved.
//

#ifndef __ThreadTutorial__Utility__
#define __ThreadTutorial__Utility__

#include <iostream>
#include "GDMacros.h"

NS_GD_BEGIN

class Utility
{
public:
    static std::string PathToFileName(const std::string& path);
    static void AtomLog(const char* formate,...);
    static void Log(const char* formate,...);
private:
    static void _AtomLog(const char* formate,va_list arg_list);
    static void _Log(const char* formate,va_list arg_list);
};

NS_GD_END

#endif /* defined(__ThreadTutorial__Utility__) */
