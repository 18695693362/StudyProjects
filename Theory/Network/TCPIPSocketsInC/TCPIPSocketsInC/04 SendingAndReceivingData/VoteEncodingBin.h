//
//  VoteEncodingBin.h
//  TCPIPSocketsInC
//
//  Created by Guo Dong on 3/8/15.
//  Copyright (c) 2015 guodong. All rights reserved.
//

#ifndef __TCPIPSocketsInC__VoteEncodingBin__
#define __TCPIPSocketsInC__VoteEncodingBin__

#include <stdio.h>
#include <stdint.h>
#include "VoteProtocol.h"

bool Decode_Bin(uint8_t* in_buf, size_t size, VoteInfo* vote_info);
size_t Encode_Bin(VoteInfo* vote_info, uint8_t* out_buf, size_t buf_size);

#endif /* defined(__TCPIPSocketsInC__VoteEncodingBin__) */
