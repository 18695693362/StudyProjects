//
//  VoteEncodingText.h
//  TCPIPSocketsInC
//
//  Created by Guo Dong on 3/7/15.
//  Copyright (c) 2015 guodong. All rights reserved.
//

#ifndef __TCPIPSocketsInC__VoteEncodingText__
#define __TCPIPSocketsInC__VoteEncodingText__

#include <stdio.h>

#include "VoteProtocol.h"

bool Decode_Text(uint8_t* in_buf, size_t size, VoteInfo* vote_info);
size_t Encode_Text(VoteInfo* vote_info, uint8_t* out_buf, size_t buf_size);

#endif /* defined(__TCPIPSocketsInC__VoteEncodingText__) */
