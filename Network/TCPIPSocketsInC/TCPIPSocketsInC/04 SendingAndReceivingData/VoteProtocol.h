//
//  VoteProtocol.h
//  TCPIPSocketsInC
//
//  Created by Guo Dong on 3/7/15.
//  Copyright (c) 2015 guodong. All rights reserved.
//

#ifndef TCPIPSocketsInC_VoteProtocol_h
#define TCPIPSocketsInC_VoteProtocol_h

#include <stdint.h>

struct VoteInfo
{
    uint64_t    count;
    int         candidate_id;
    bool        is_inquiry;
    bool        is_response;
};

typedef struct VoteInfo VoteInfo;

enum {
    MAX_CANDIDATE = 1000,
    MAX_WIRE_SIZE = 500
};

#endif
