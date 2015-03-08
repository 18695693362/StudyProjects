//
//  VoteEncoding.cpp
//  TCPIPSocketsInC
//
//  Created by Guo Dong on 3/7/15.
//  Copyright (c) 2015 guodong. All rights reserved.
//

#include "VoteEncoding.h"
#include "VoteEncodingText.h"
#include "VoteEncodingBin.h"

bool Decode(uint8_t* in_buf, size_t size, VoteInfo* vote_info, EncodeType type)
{
    if (type==EncodeType::kText)
    {
        return Decode_Text(in_buf, size, vote_info);
    }
    else
    {
        return Decode_Bin(in_buf, size, vote_info);
    }
}

size_t Encode(VoteInfo* vote_info, uint8_t* out_buf, size_t buf_size, EncodeType type)
{
    if (type==EncodeType::kText)
    {
        return Encode_Text(vote_info, out_buf, buf_size);
    }
    else
    {
        return Encode_Bin(vote_info, out_buf, buf_size);
    }
}