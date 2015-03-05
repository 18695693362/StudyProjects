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
    
    static void PrintSocketAddress(const struct sockaddr* address, FILE* stream);
    static void PrintLocalForeignAddress(int socket,FILE* stream);
    
    static void BindSocket(int socket,unsigned int port,FILE* stream);
    template<typename SrcDataType>
    static void PrintWithBinaryFormat(FILE* stream,SrcDataType data,size_t bytes_len=0);
};

#endif /* defined(__TCPIPSocketsInC__GUtility__) */
