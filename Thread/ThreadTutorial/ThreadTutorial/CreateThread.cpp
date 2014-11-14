//
//  CreateThread.cpp
//  ThreadTutorial
//
//  Created by guodong on 4/2/14.
//  Copyright (c) 2014 guodong. All rights reserved.
//

#include "CreateThread.h"
#include <thread>
#include <chrono>
#include "Utility.h"

using namespace std;
USING_NS_GD;

void thread_function_for0_main_000(string s)
{
    printf("%s::%s: thread function(%s)\n",
           Utility::PathToFileName(__FILE__).c_str(),
           __FUNCTION__,
           s.c_str());
}

void thread_function_with_sarg_000(string s)
{
    s = "thread_function_with_sarg_000";
    printf("%s::%s: thread function(%s)\n",
           Utility::PathToFileName(__FILE__).c_str(),
           __FUNCTION__,
           s.c_str());
}

void thread_function_with_sref_arg(string& s)
{
    s = "thread_function_with_sref_arg";
    printf("%s::%s: thread function(%s)\n",
           Utility::PathToFileName(__FILE__).c_str(),
           __FUNCTION__,
           s.c_str());
}

void thread_function_sleep(int n)
{
    printf("%s::%s: thread function(thread_function_sleep(%d))\n",
           Utility::PathToFileName(__FILE__).c_str(),
           __FUNCTION__,
           n);
    std::this_thread::sleep_for(std::chrono::seconds(n));
    std::cout << n << ": " << std::this_thread::get_id() << endl;
}

void CreateThreadTest()
{
    std::string s = "thread_function_for0_main_000";
    thread t1(&thread_function_with_sarg_000,s);
    
    //thread t2(&thread_function_with_sref_arg,s);  // compile error
    thread t2(&thread_function_with_sref_arg,std::ref(s));
    t1.join();
    t2.join();
    thread_function_for0_main_000(s);
}

void CreateThreadDetach()
{
    std::string s = __FUNCTION__;
    //thread t(thread_function_with_sarg_000,std::ref(s));
    //t.detach();
}

void TestMoveThread()
{
    std::thread threads[5];
    for (int i=0; i<5; i++)
    {
// thread move copy operator
// move                  thread& operator= (thread&& rhs) noexcept;
// copy [deleted] (2)    thread& operator= (const thread&) = delete;
        // 这里是move操作 而不是通常意义的复制操作
        threads[i] = std::thread(thread_function_sleep, i+1);
    }
    for (auto& t : threads)
    {
        t.join();
    }
}



