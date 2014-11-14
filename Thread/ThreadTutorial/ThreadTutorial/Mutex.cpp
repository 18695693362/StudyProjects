//
//  Mutex.cpp
//  ThreadTutorial
//
//  Created by guodong on 4/2/14.
//  Copyright (c) 2014 guodong. All rights reserved.
//

#include "Mutex.h"
#include <thread>
#include <mutex>
#include <iostream>
#include <chrono>
#include <stdexcept>

using namespace std;

volatile int g_counter = 0;
//int g_counter = 0;
std::mutex g_counter_mutex;
std::timed_mutex g_counter_time_mutex;

void thread_function_increase()
{
    for (int i=0; i<3; i++)
    {
        if(g_counter_mutex.try_lock())
            //g_counter_mutex.lock();
        {
            ++g_counter;
            cout << this_thread::get_id() << ": " << i << endl;
            g_counter_mutex.unlock();
            this_thread::sleep_for(std::chrono::seconds(2));
        }
    }
}

void thread_function_increase_timemutex()
{
    for (int i=0; i<5; i++)
    {
        if(g_counter_time_mutex.try_lock_for(std::chrono::seconds(1)))
            //g_counter_mutex.lock();
        {
            ++g_counter;
            cout << this_thread::get_id() << ": " << i << endl;
            g_counter_time_mutex.unlock();
            this_thread::sleep_for(std::chrono::seconds(2));
        }
    }
}

void TestMutex()
{
    std::thread threads[5];
    for (auto& temp : threads)
    {
        temp = thread(thread_function_increase);
    }
    for (auto& temp : threads)
    {
        temp.join();
    }
    
    cout << __FUNCTION__ << " g_counter:" << g_counter << endl;
}

void TestTimeMutex()
{
    std::thread threads[5];
    for (auto& temp : threads)
    {
        temp = thread(thread_function_increase_timemutex);
    }
    for (auto& temp : threads)
    {
        temp.join();
    }
    
    cout << __FUNCTION__ << " g_counter:" << g_counter << endl;
}





