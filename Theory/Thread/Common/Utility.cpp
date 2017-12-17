//
//  Utility.cpp
//  ThreadTutorial
//
//  Created by guodong on 4/2/14.
//  Copyright (c) 2014 guodong. All rights reserved.
//

#include "Utility.h"
#include <mutex>
using namespace std;
USING_NS_GD;

string Utility::PathToFileName(const std::string &path)
{
    string name;
    size_t pos = path.rfind("/");
    pos = pos!=std::string::npos ? pos : path.rfind("\\");
    if (pos!=std::string::npos)
    {
        name = path.substr(pos);
        if (name.length()>0)
        {
            name = name.substr(1);
        }
    }
    return name;
}

recursive_mutex _atom_log_mutex;
void Utility::AtomLog(const char* formate,...)
{
    _atom_log_mutex.lock();
    va_list arg_list;
    va_start(arg_list, formate);
    _AtomLog(formate, arg_list);
    va_end(arg_list);
    _atom_log_mutex.unlock();
}

void Utility::Log(const char* formate,...)
{
    va_list arg_list;
    va_start(arg_list, formate);
    _Log(formate, arg_list);
    va_end(arg_list);
}

char _atom_log_buff[16*1024]={0};
void Utility::_AtomLog(const char* formate,va_list arg_list)
{
    memset(_atom_log_buff, 0, 16*1024);
    vsnprintf(_atom_log_buff, 16*1024, formate, arg_list);
    strcat(_atom_log_buff, "\n");
    fprintf(stdout, "wolfand11: %s", _atom_log_buff);
    fflush(stdout);
}

char _log_buff[16*1024]={0};
void Utility::_Log(const char* formate,va_list arg_list)
{
    memset(_log_buff, 0, 16*1024);
    vsnprintf(_log_buff, 16*1024, formate, arg_list);
    strcat(_log_buff, "\n");
    fprintf(stdout, "wolfand11: %s", _log_buff);
    fflush(stdout);
}






