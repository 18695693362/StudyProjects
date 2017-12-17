//
//  LengthFramer.h
//  TCPIPSocketsInC
//
//  Created by Guo Dong on 3/7/15.
//  Copyright (c) 2015 guodong. All rights reserved.
//

#ifndef __TCPIPSocketsInC__LengthFramer__
#define __TCPIPSocketsInC__LengthFramer__

#include <stdio.h>

int GetNextMsg_Length(FILE* in, uint8_t* buf, size_t buf_size);
int PutMsg_Length(uint8_t buf[], size_t msg_size, FILE* out);

#endif /* defined(__TCPIPSocketsInC__LengthFramer__) */
