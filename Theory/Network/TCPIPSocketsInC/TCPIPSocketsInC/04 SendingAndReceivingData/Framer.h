//
//  Framer.h
//  TCPIPSocketsInC
//
//  Created by Guo Dong on 3/7/15.
//  Copyright (c) 2015 guodong. All rights reserved.
//

#ifndef __TCPIPSocketsInC__Framer__
#define __TCPIPSocketsInC__Framer__

#include <stdio.h>
#include <stdint.h>

enum FramerType
{
    kDelimFramer    = 1,
    kLengthFramer   = 2
};

int GetNextMsg(FILE* in, uint8_t* buf, size_t buf_size, FramerType type=FramerType::kLengthFramer);
int PutMsg(uint8_t buf[], size_t msg_size, FILE* out, FramerType type=FramerType::kLengthFramer);

#endif /* defined(__TCPIPSocketsInC__Framer__) */
