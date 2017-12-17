//
//  DelimFramer.h
//  TCPIPSocketsInC
//
//  Created by Guo Dong on 3/7/15.
//  Copyright (c) 2015 guodong. All rights reserved.
//

#ifndef __TCPIPSocketsInC__DelimFramer__
#define __TCPIPSocketsInC__DelimFramer__

#include <stdio.h>

int GetNextMsg_Delim(FILE* in, uint8_t* buf, size_t buf_size);
int PutMsg_Delim(uint8_t buf[], size_t msg_size, FILE* out);

#endif /* defined(__TCPIPSocketsInC__DelimFramer__) */
