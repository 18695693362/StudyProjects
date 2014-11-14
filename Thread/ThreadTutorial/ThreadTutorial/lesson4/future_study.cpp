//
//  future_study.cpp
//  ThreadTutorial
//
//  Created by Guo Dong on 10/2/14.
//  Copyright (c) 2014 Guo Dong. All rights reserved.
//

#include "future_study.h"
#include <string>
#include <mutex>
#include <thread>
#include <future>
#include <iostream>
#include "Utility.h"


using namespace std;
using namespace wolfand11;

// thread func
// - for simple future
void print_future_state(future<int>& arg_future)
{
    int x = arg_future.get();
    cout << "SubThread: " << this_thread::get_id() << " x=" << x << endl;
    this_thread::sleep_for(chrono::seconds(1));
}
// - for shared_state lifetime
void print_future_state_1(future<int>& arg_future)
{
    int x = arg_future.get();
    cout << "SubThread: " << this_thread::get_id() << " x=" << x << endl;
    this_thread::sleep_for(chrono::seconds(3));
    Utility::AtomLog("SubThread %x future over",this_thread::get_id());
}
void create_promise()
{
    promise<int> t_promise;
    future<int>t_future = t_promise.get_future();
    cout << "SubThread: " << this_thread::get_id() << " create promise" << endl;
    thread print_future_state_t(print_future_state_1,ref(t_future));
    t_promise.set_value(10);
    print_future_state_t.detach();
    Utility::AtomLog("SubThread %x promise over",this_thread::get_id());
}
// -for packaged_task
int count_down_func(int from, int to)
{
    int ret = from-to;
    for (int i=from; i>to; i--)
    {
        cout << i << endl;
        this_thread::sleep_for(chrono::seconds(1));
        if (i==0)
        {
            ret++;
            break;
        }
    }
    cout << "CountOver" << endl;
    return ret;
}
// thread creator
void simple_future_test(void(*func)(future<int>&))
{
    promise<int> t_promise;
    future<int> t_future = t_promise.get_future();
    
    const int thread_count = 1;
    //const int thread_count = 2;
    //thread_count = 2; will crash
    thread ts[thread_count];
    for (auto& t : ts)
    {
        t = thread(func, std::ref(t_future));
    }
    t_promise.set_value(10);
    for (auto& t : ts)
    {
        t.join();
    }
    Utility::AtomLog("MainThread %x",this_thread::get_id());
}

void shared_state_lifetime_testvoid()
{
    thread create_promise_thread(create_promise);
    create_promise_thread.join();
    this_thread::sleep_for(chrono::seconds(1));
    Utility::AtomLog("MainThread %x",this_thread::get_id());
    this_thread::sleep_for(chrono::seconds(4));
}

void packaged_task_test()
{
    std::packaged_task<int(int,int)> count_down_task(&count_down_func);
    future<int> ret = count_down_task.get_future();
    
    thread t(std::move(count_down_task),10,0);
    int result_value = ret.get();
    cout << "MainThread " << this_thread::get_id() << ": ret=" << result_value << endl;
    
    t.join();
}

// test func
void lesson4_test()
{
//    simple_future_test(print_future_state);
//    shared_state_lifetime_testvoid();
    packaged_task_test();
}