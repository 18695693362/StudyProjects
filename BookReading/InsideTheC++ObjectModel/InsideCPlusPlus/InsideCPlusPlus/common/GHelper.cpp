//
//  GHelper.cpp
//  InsideCPlusPlus
//
//  Created by Guo Dong on 7/9/16.
//  Copyright © 2016 Guo Dong. All rights reserved.
//

#include "GHelper.h"
#include <iostream>

using namespace std;

GCodeTimer& GCodeTimer::GetInstance()
{
    static GCodeTimer code_timer("Global CodeTimer");
    return code_timer;
}

void GCodeTimer::Record(const char* info)
{
    typedef chrono::duration<double> Duration;
    TimePoint cur_time = Clock::now();
    Duration time_span = chrono::duration_cast<Duration>(cur_time - pre_record_time_);
    std::cout << name_ << " [" << info << "] : ";
    printf("%.5f\n",time_span.count());
    
    pre_record_time_ = cur_time;
}

void GCodeTimer::Reset()
{
    pre_record_time_ = Clock::now();
}

void GHelper::PrintLocalTime()
{
    
}