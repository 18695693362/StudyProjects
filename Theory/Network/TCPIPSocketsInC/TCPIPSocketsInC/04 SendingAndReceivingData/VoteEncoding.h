//
//  VoteEncoding.h
//  TCPIPSocketsInC
//
//  Created by Guo Dong on 3/7/15.
//  Copyright (c) 2015 guodong. All rights reserved.
//

#ifndef __TCPIPSocketsInC__VoteEncoding__
#define __TCPIPSocketsInC__VoteEncoding__

#include <stdio.h>
#include "VoteProtocol.h"

enum EncodeType
{
    kText = 1,
};

bool Decode(uint8_t* in_buf, size_t size, VoteInfo* vote_info, EncodeType type=EncodeType::kText);
size_t Encode(VoteInfo* vote_info, uint8_t* out_buf, size_t buf_size, EncodeType type=EncodeType::kText);

#endif /* defined(__TCPIPSocketsInC__VoteEncoding__) */
