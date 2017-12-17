//
//  LengthFramer.cpp
//  TCPIPSocketsInC
//
//  Created by Guo Dong on 3/7/15.
//  Copyright (c) 2015 guodong. All rights reserved.
//
#include <stdint.h>
#include <netdb.h>
#include "LengthFramer.h"

#define BUFSIZE 100

int GetNextMsg_Length(FILE* in, uint8_t* buf, size_t buf_size)
{
    uint16_t msg_size   = 0;
    uint16_t extra      = 0;
    
    if (fread(&msg_size, sizeof(uint16_t), 1, in)!=1)
    {
        return -1;
    }
    msg_size = ntohs(msg_size);
    if (msg_size > buf_size)
    {
        extra = msg_size - buf_size;
        msg_size = buf_size;
    }
    if (fread(buf, sizeof(uint8_t), msg_size, in)!=msg_size)
    {
        fprintf(stderr, "Framing error: expected %d, read less\n", msg_size);
        return -1;
    }
    if (extra > 0)
    {
        uint8_t waste[BUFSIZE];
        fread(waste, sizeof(uint8_t), extra, in);
        return -(msg_size+extra);
    }
    else
    {
        return msg_size;
    }
}

int PutMsg_Length(uint8_t buf[], size_t msg_size, FILE* out)
{
    if (msg_size>UINT16_MAX)
    {
        return -1;
    }
    uint16_t payload_size = htons(msg_size);
    if ( (fwrite(&payload_size, sizeof(uint16_t), 1, out)!=1) ||
         (fwrite(buf, sizeof(uint8_t), msg_size, out)!=msg_size) )
    {
        return -1;
    }
    fflush(out);
    return msg_size;
}