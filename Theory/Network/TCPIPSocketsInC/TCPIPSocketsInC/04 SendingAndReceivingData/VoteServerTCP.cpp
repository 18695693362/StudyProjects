//
//  VoteServerTCP.cpp
//  TCPIPSocketsInC
//
//  Created by Guo Dong on 3/7/15.
//  Copyright (c) 2015 guodong. All rights reserved.
//

#include "VoteServerTCP.h"
#include "TCPServerUtility.h"
#include "GUtility.h"
#include "VoteProtocol.h"
#include "VoteEncoding.h"
#include "Framer.h"

static uint64_t counts[MAX_CANDIDATE+1];

void RunVoteServer(const char* service)
{
    int serv_socket = SetupTCPServerSocket(service);
    
    while (true)
    {
        int client_sock = AcceptTCPConnection(serv_socket);
        
        FILE* channel = fdopen(client_sock, "r+");
        if (channel == nullptr)
        {
            GUtility::DieWithSystemMessage("fdopen() failed");
        }
        
        int msg_size;
        uint8_t inbuf[MAX_WIRE_SIZE];
        VoteInfo vote_info;
        while ((msg_size=GetNextMsg(channel, inbuf, MAX_WIRE_SIZE)) > 0)
        {
            memset(&vote_info, 0, sizeof(vote_info));
            printf("Received message (%d bytes)\n", msg_size);
            if (Decode(inbuf, msg_size, &vote_info))
            {
                if (!vote_info.is_response)
                {
                    vote_info.is_response = true;
                    if (vote_info.candidate_id>=0 && vote_info.candidate_id<=MAX_CANDIDATE)
                    {
                        if (!vote_info.is_inquiry)
                        {
                            counts[vote_info.candidate_id] += 1;
                        }
                        vote_info.count = counts[vote_info.candidate_id];
                    }
                }
                
                uint8_t outbuf[MAX_WIRE_SIZE];
                msg_size = Encode(&vote_info, outbuf, MAX_WIRE_SIZE);
                if (PutMsg(outbuf, msg_size, channel) < 0)
                {
                    fputs("Error framing/outputting message\n", stderr);
                    break;
                }
                else
                {
                    printf("Processed %s for candidate %d; current count is %llu.\n",
                           (vote_info.is_inquiry ? "inquiry" : "vote"), vote_info.candidate_id, vote_info.count);
                }
                fflush(channel);
            }
            else
            {
                fputs("Parse error, closing connection.\n", stderr);
                break;
            }
        }
    }
}

void Test04_TestVoteServer(bool is_run)
{
    if (!is_run)
    {
        return;
    }
    RunVoteServer("7777");
}