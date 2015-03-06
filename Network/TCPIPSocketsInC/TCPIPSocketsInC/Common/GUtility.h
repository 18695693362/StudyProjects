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
#include <functional>

enum GByteOrderType
{
    kInvalid            = 0,
    kLittleEndianOrder  = 1,
    kBigEndianOrder     = 2,
};

class GUtility
{
public:
    static void DieWithUserMessage(const std::string& msg,const std::string& detail="");
    static void DieWithSystemMessage(const std::string&msg);
    
    static void PrintSocketAddress(const struct sockaddr* address, FILE* stream);
    static void PrintLocalForeignAddress(int socket,FILE* stream);
    
    static void BindSocket(int socket,unsigned int port,FILE* stream);
    static GByteOrderType CheckSystemByteOrderType();
};

template<typename SrcDataType>
static void PrintWithBinaryFormat(FILE* stream,SrcDataType data,int bytes_len=0,GByteOrderType byte_order_type=GByteOrderType::kInvalid)
{
    if (bytes_len==0)
    {
        bytes_len = sizeof(SrcDataType);
    }
    if (byte_order_type==GByteOrderType::kInvalid)
    {
        byte_order_type = GUtility::CheckSystemByteOrderType();
    }
    
    std::function<void(char,FILE*)> _PrintByteToBinaryStr = [](char c,FILE* stream)
    {
        for (int i=7; i>-1; i--)
        {
            if ((1<<i & c) == 0)
            {
                fputs("0", stream);
            }
            else
            {
                fputs("1", stream);
            }
        }
    };
    
    if(byte_order_type==GByteOrderType::kLittleEndianOrder)
    {
        for (int i=bytes_len-1; i>-1; i--)
        {
            _PrintByteToBinaryStr(((char*)&data)[i],stream);
        }
    }
    else
    {
        for (int i=0; i<bytes_len; i++)
        {
            _PrintByteToBinaryStr(((char*)&data)[i],stream);
        }
    }
    fputc('\n', stream);
}

#endif /* defined(__TCPIPSocketsInC__GUtility__) */
