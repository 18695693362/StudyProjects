//
//  SigAction.cpp
//  TCPIPSocketsInC
//
//  Created by Guo Dong on 3/8/15.
//  Copyright (c) 2015 guodong. All rights reserved.
//
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

#include "SigAction.h"
#include "GUtility.h"

void InterruptSignalHander(int signal_type);
void InterruptSignalHander(int signal_type)
{
    puts("Interrupt Received. Exiting program.");
    //exit(1);
    sleep(3);
}

void RunSigAnction()
{
    struct sigaction handler;
    
    handler.sa_handler = InterruptSignalHander;
    if (sigfillset(&handler.sa_mask) < /* DISABLES CODE */ (0))
    {
        GUtility::DieWithSystemMessage("sigfillset() failed");
    }
    handler.sa_flags = 0;
    
    if (sigaction(SIGINT, &handler, 0))
    {
        GUtility::DieWithSystemMessage("sigaction() failed for SIGINT");
    }
    
    while (true)
    {
        pause();
    }
}

void Test05_TestSigAction(bool is_run)
{
    if (!is_run)
    {
        return;
    }
    RunSigAnction();
    exit(0);
}