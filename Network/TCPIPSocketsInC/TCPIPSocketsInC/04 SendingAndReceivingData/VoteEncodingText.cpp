//
//  VoteEncodingText.cpp
//  TCPIPSocketsInC
//
//  Created by Guo Dong on 3/7/15.
//  Copyright (c) 2015 guodong. All rights reserved.
//
#include <string.h>
#include <stdlib.h>

#include "VoteEncodingText.h"

static const char* MAGIC        = "Voting";
static const char* VOTESTR      = "v";
static const char* INQSTR       = "i";
static const char* RESPONSESTR  = "R";
static const char* DELIMSTR     = " ";

enum
{
    BASE = 10
};

size_t Encode_Text(VoteInfo* vote_info, uint8_t* out_buf, size_t buf_size)
{
    uint8_t* buf_ptr = out_buf;
    long size = buf_size;
    int rv= snprintf((char*)buf_ptr, size, "%s %c %s %d",MAGIC,(vote_info->is_inquiry ? 'i' : 'v'),(vote_info->is_response ? "R" : ""),vote_info->candidate_id);
    buf_ptr += rv;
    size -= rv;
    if (vote_info->is_response)
    {
        rv = snprintf((char*)buf_ptr, size, "%llu", vote_info->count);
    }
    return (size_t) (buf_ptr-out_buf);
}

bool Decode_Text(uint8_t* in_buf, size_t size, VoteInfo* vote_info)
{
    char* token = nullptr;
    token = strtok((char*)in_buf, DELIMSTR);
    if (token == nullptr || strcmp(token, MAGIC))
    {
        return false;
    }
    token = strtok(nullptr, DELIMSTR);
    if (token == nullptr)
    {
        return false;
    }
    if (strcmp(token, VOTESTR) == 0)
    {
        vote_info->is_inquiry = false;
    }
    else if (strcmp(token, INQSTR) == 0)
    {
        vote_info->is_inquiry = true;
    }
    else
    {
        return false;
    }
    
    token = strtok(nullptr, DELIMSTR);
    if (token==nullptr)
    {
        return false;
    }
    if (strcmp(token, RESPONSESTR)==0)
    {
        vote_info->is_response = true;
        token = strtok(nullptr, DELIMSTR);
        if (token==nullptr)
        {
            return false;
        }
        else
        {
            vote_info->is_response = false;
        }
    }
    vote_info->candidate_id = atoi(token);
    if (vote_info->is_response)
    {
        token = strtok(nullptr, DELIMSTR);
        if (token==nullptr)
        {
            return false;
        }
        vote_info->count = strtoll(token, nullptr, BASE);
    }
    else
    {
        vote_info->count = 0L;
    }
    return true;
}

