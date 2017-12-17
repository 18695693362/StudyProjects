//
//  VoteEncodingBin.cpp
//  TCPIPSocketsInC
//
//  Created by Guo Dong on 3/8/15.
//  Copyright (c) 2015 guodong. All rights reserved.
//

#include <netdb.h>

#include "VoteEncodingBin.h"
#include "GUtility.h"

enum {
    REQUEST_SIZE = 4,
    RESPONSE_SIZE =12,
    COUNT_SHIFT     = 32,
    INQUIRE_FLAG    = 0x0100,
    RESPONSE_FLAG   = 0x0200,
    MAGIC           = 0x5400,
    MAGIC_MASK      = 0xfc00
};

typedef struct VoteMsgBin VoteMsgBin;

struct VoteMsgBin {
    uint16_t header;
    uint16_t candidate_id;
    uint32_t count_high;
    uint32_t count_low;
};

bool Decode_Bin(uint8_t* in_buf, size_t size, VoteInfo* vote_info)
{
    VoteMsgBin* vote_msg = (VoteMsgBin*) in_buf;
    uint16_t header = ntohs(vote_msg->header);
    if ((size<REQUEST_SIZE) || ((header & MAGIC_MASK)!=MAGIC))
    {
        return false;
    }
    vote_info->is_response = ((header & RESPONSE_FLAG)!=0);
    vote_info->is_inquiry  = ((header & INQUIRE_FLAG)!=0);
    if (vote_info->is_response && size>=RESPONSE_SIZE)
    {
        vote_info->count = ((uint64_t)ntohl(vote_msg->count_high)<<COUNT_SHIFT) | (uint64_t)ntohl(vote_msg->count_low);
    }
    return true;
}

size_t Encode_Bin(VoteInfo* vote_info, uint8_t* out_buf, size_t buf_size)
{
    if ((vote_info->is_response && buf_size<sizeof(VoteMsgBin)) || buf_size<2)
    {
        GUtility::DieWithUserMessage("Output buffer too small");
    }
    VoteMsgBin* vote_msg = (VoteMsgBin*)out_buf;
    memset(out_buf, 0, sizeof(VoteMsgBin));
    vote_msg->header = MAGIC;
    if (vote_info->is_inquiry)
    {
        vote_msg->header |= INQUIRE_FLAG;
    }
    if (vote_info->is_response)
    {
        vote_msg->header |= RESPONSE_FLAG;
    }
    vote_msg->header = htons(vote_msg->header);
    vote_msg->candidate_id = htons(vote_info->candidate_id);
    if (vote_info->is_response)
    {
        vote_msg->count_high = htonl(vote_info->count>>COUNT_SHIFT);
        vote_msg->count_low = htonl((uint32_t)vote_info->count);
        return RESPONSE_SIZE;
    }
    else
    {
        return REQUEST_SIZE;
    }
}








