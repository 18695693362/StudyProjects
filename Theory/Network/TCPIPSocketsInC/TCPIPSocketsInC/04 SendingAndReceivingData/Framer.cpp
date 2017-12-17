//
//  Framer.cpp
//  TCPIPSocketsInC
//
//  Created by Guo Dong on 3/7/15.
//  Copyright (c) 2015 guodong. All rights reserved.
//

#include "Framer.h"
#include "DelimFramer.h"
#include "LengthFramer.h"

int GetNextMsg(FILE* in, uint8_t* buf, size_t buf_size, FramerType type)
{
    if (type==FramerType::kDelimFramer)
    {
        return GetNextMsg_Delim(in, buf, buf_size);
    }
    else
    {
        return GetNextMsg_Length(in, buf, buf_size);
    }
}

int PutMsg(uint8_t buf[], size_t msg_size, FILE* out, FramerType type)
{
    if (type==FramerType::kDelimFramer)
    {
        return PutMsg_Delim(buf, msg_size, out);
    }
    else
    {
        return PutMsg_Length(buf, msg_size, out);
    }
}