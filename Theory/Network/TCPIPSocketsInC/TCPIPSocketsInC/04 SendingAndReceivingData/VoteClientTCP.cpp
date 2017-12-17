//
//  VoteClientTCP.cpp
//  TCPIPSocketsInC
//
//  Created by Guo Dong on 3/7/15.
//  Copyright (c) 2015 guodong. All rights reserved.
//
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "VoteClientTCP.h"
#include "GUtility.h"
#include "VoteProtocol.h"
#include "TCPClientUtility.h"
#include "VoteEncoding.h"
#include "Framer.h"

void RunVoteClient(const char* server,const char* service,const char* candi,bool is_inquiry=false);
void RunVoteClient(const char* server,const char* service,const char* candi,bool is_inquiry)
{
    int candi_id = atoi(candi);
    if (candi_id<0 || candi_id>MAX_CANDIDATE)
    {
        GUtility::DieWithUserMessage("Candidate not valid",candi);
    }
    int sock = SetupTCPClientSocket(server, service);
    if (sock<0)
    {
        GUtility::DieWithUserMessage("SetupTCPClientSocket() failed","unable to connect");
    }
    
    FILE* str = fdopen(sock, "r+");
    if (str==nullptr)
    {
        GUtility::DieWithUserMessage("fdopen() failed");
    }
    VoteInfo vote_info;
    memset(&vote_info, 0, sizeof(vote_info));
    vote_info.is_inquiry   = is_inquiry;
    vote_info.candidate_id = candi_id;
    
    uint8_t outbuf[MAX_WIRE_SIZE];
    size_t req_size = Encode(&vote_info, outbuf, MAX_WIRE_SIZE);
    
    printf("Sending %zu-byte %s for candidate %d...\n",req_size,(is_inquiry ? "inquiry" : "vote"), candi_id);
    if (PutMsg(outbuf, req_size, str) < 0)
    {
        GUtility::DieWithSystemMessage("PutMsg() failed");
    }
    
    uint8_t inbuf[MAX_WIRE_SIZE];
    size_t resp_size = GetNextMsg(str, inbuf, MAX_WIRE_SIZE);
    if (Decode(inbuf, resp_size, &vote_info))
    {
        printf("Received:\n");
        if (vote_info.is_response)
        {
            printf(" Response to ");
        }
        if (vote_info.is_inquiry)
        {
            printf("inquiry ");
        }
        else
        {
            printf("vote ");
        }
        printf("for condidate %d\n", vote_info.candidate_id);
        if (vote_info.is_response)
        {
            printf(" count = %llu\n", vote_info.count);
        }
    }
    
    fclose(str);
}

void Test04_TestVoteClient(bool is_run)
{
    if (!is_run)
    {
        return;
    }
    
    RunVoteClient("127.0.0.1", "7777", "1", false);
    RunVoteClient("127.0.0.1", "7777", "1", true);
}