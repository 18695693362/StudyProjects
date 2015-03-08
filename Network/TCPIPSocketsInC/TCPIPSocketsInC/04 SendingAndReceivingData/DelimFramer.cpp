//
//  DelimFramer.cpp
//  TCPIPSocketsInC
//
//  Created by Guo Dong on 3/7/15.
//  Copyright (c) 2015 guodong. All rights reserved.
//

#include <stdint.h>

#include "DelimFramer.h"
#include "GUtility.h"

static const char DELIMITER = '\n';

int GetNextMsg_Delim(FILE* in, uint8_t* buf, size_t buf_size)
{
    int count = 0;
    int next_char = 0;
    while (count<buf_size)
    {
        next_char = getc(in);
        if (next_char == EOF)
        {
            if (count>0)
            {
                GUtility::DieWithUserMessage("GetNextMsg()","Stream ended prematurely");
            }
            else
            {
                return -1;
            }
        }
        else if (next_char == DELIMITER)
        {
            break;
        }
        buf[count++] = next_char;
    }
    if (next_char != DELIMITER)
    {
        return -count;
    }
    else
    {
        return count;
    }
}

int PutMsg_Delim(uint8_t buf[], size_t msg_size, FILE* out)
{
    int i = 0;
    for (i=0; i<msg_size; i++)
    {
        if (buf[i] == DELIMITER)
        {
            return -1;
        }
    }
    if (fwrite(buf, 1, msg_size, out)!=msg_size)
    {
        return -1;
    }
    fputc(DELIMITER, out);
    fflush(out);
    fflush(out);
    return msg_size;
}