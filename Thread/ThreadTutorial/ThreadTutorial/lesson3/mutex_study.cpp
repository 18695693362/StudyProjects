//
//  mutex_study.cpp
//  ThreadTutorial
//
//  Created by guodong on 9/30/14.
//  Copyright (c) 2014 guodong. All rights reserved.
//

#include "mutex_study.h"
#include <thread>
#include <mutex>
#include <iostream>
#include <chrono>
#include "Utility.h"

using namespace std;

// global
//-- for simple_mutex
mutex sum_mutex;
int value = 0;
mutex sum_mutex_1;
int value_1 = 0;
// thread func
void accumulator_func()
{
    sum_mutex.lock();
    // test deadlock
    sum_mutex.lock();
    value++;
    cout << "SubThread("<<this_thread::get_id()<<"):"<< value << endl;
    sum_mutex.unlock();
}

void accumulator_func_1()
{
    if (sum_mutex_1.try_lock())
    {
        //test deadlock
        sum_mutex_1.lock();
        value_1++;
        wolfand11::Utility::AtomLog("SubThread %x :%d",this_thread::get_id(),value_1);
    }
    else
    {
        wolfand11::Utility::AtomLog("SubThread %x :try lock false!",this_thread::get_id());
    }
    sum_mutex_1.unlock();
}

void accumulator_func_1_1()
{
    sum_mutex_1.lock();
    //test deadlock
    if (sum_mutex_1.try_lock())
    {
        value_1++;
        wolfand11::Utility::AtomLog("SubThread %x :%d",this_thread::get_id(),value_1);
    }
    else
    {
        wolfand11::Utility::AtomLog("SubThread %x :try lock false!",this_thread::get_id());
    }
    sum_mutex_1.unlock();
}

//-- for recursive_mutex
recursive_mutex sum_mutex_2;
int value_2 = 0;
void accumulator_func_2()
{
    sum_mutex_2.lock();
    sum_mutex_2.lock();
    value_2++;
    value_2++;
    cout << "SubThread("<<this_thread::get_id()<<"):"<< value_2 << endl;
    sum_mutex_2.unlock();
    sum_mutex_2.unlock();
}

//-- for time_mutex
timed_mutex sum_mutex_3;
timed_mutex sum_mutex_3_1;
timed_mutex sum_mutex_3_2;
timed_mutex sum_mutex_3_3;
int value_3 = 0;
int value_3_1 = 0;
int value_3_2 = 0;
int value_3_3 = 0;
void accumulator_func_3()
{
    while (true)
    {
        if(sum_mutex_3.try_lock_for(chrono::seconds(1)))
        {
            value_3++;
            wolfand11::Utility::AtomLog("SubThread %x :%d",this_thread::get_id(),value_3);
            this_thread::sleep_for(chrono::seconds(2));
            sum_mutex_3.unlock();
        }
        else
        {
            wolfand11::Utility::AtomLog("SubThread %x :sleep",this_thread::get_id());
            this_thread::sleep_for(chrono::seconds(1));
        }
    }
}
void accumulator_func_3_1()
{
    while (sum_mutex_3_1.try_lock_for(chrono::seconds(2)))
    {
        value_3_1++;
        wolfand11::Utility::AtomLog("SubThread %x :%d",this_thread::get_id(),value_3_1);
        if (sum_mutex_3_1.try_lock_for(chrono::seconds(1)))
        {
            wolfand11::Utility::AtomLog("SubThread:try_lock_for true");
        }
        else
        {
            wolfand11::Utility::AtomLog("SubThread:try_lock_for false");
        }
    }
    //this_thread::sleep_for(chrono::seconds(1));
    wolfand11::Utility::AtomLog("SubThread %x :timeout",this_thread::get_id());
    sum_mutex_3_1.unlock();
}

void accumulator_func_3_2()
{
    sum_mutex_3_2.lock();
    sum_mutex_3_2.lock();
    value_3_2++;
    wolfand11::Utility::AtomLog("SubThread %x :%d",this_thread::get_id(),value_3_2);
    sum_mutex_3_2.unlock();
    sum_mutex_3_2.unlock();
}

void accumulator_func_3_3()
{
    sum_mutex_3_3.lock();
    if(sum_mutex_3_3.try_lock_for(chrono::seconds(1)))
    {
        value_3_3++;
        wolfand11::Utility::AtomLog("SubThread %x :%d",this_thread::get_id(),value_3_3);
    }
    else
    {
        wolfand11::Utility::AtomLog("SubThread %x :first try lock failed",this_thread::get_id());
        sum_mutex_3_3.try_lock_for(chrono::seconds(1));
    }
    sum_mutex_3_3.unlock();
}

// for lock_guard
mutex my_lock_guard_mutex;
void print_id()
{
    std::lock_guard<mutex> t_lock_guard(my_lock_guard_mutex);
    cout << "SubThread:" << this_thread::get_id() << endl;
}

// for unique_lock
timed_mutex my_unique_lock_mutex;
void print_unique_lock_id()
{
    unique_lock<timed_mutex> my_unique_lock(my_unique_lock_mutex,chrono::seconds(5));
    if (my_unique_lock)
    {
        cout << "SubThread:" << this_thread::get_id() << " try_lock ture" << endl;
        this_thread::sleep_for(chrono::seconds(1));
    }
    else
    {
        wolfand11::Utility::AtomLog("SubThread %x try_lock false",this_thread::get_id());
    }
}

// thread creator
void simple_mutex()
{
    const int thread_count = 5;
    thread ts[thread_count];
    for (int i=0; i<thread_count; i++)
    {
        ts[i] = thread(accumulator_func);
    }
    for (auto& t : ts)
    {
        t.join();
    }
    
    cout << "MainThread:" << value << endl;
}

void simple_mutex_1(void(*func)())
{
    const int thread_count = 1;
    thread ts[thread_count];
    for (int i=0; i<thread_count; i++)
    {
        ts[i] = thread(func);
    }
    for (auto& t : ts)
    {
        t.join();
    }
    
    cout << "MainThread:" << value_1 << endl;
}

void recursive_mutex_test()
{
    const int thread_count = 5;
    thread ts[thread_count];
    for (int i=0; i<thread_count; i++)
    {
        ts[i] = thread(accumulator_func_2);
    }
    for (auto& t : ts)
    {
        t.join();
    }
    wolfand11::Utility::AtomLog("MainThread:%d",value_1);
}

void time_mutex_test(void(*func)(),int& value)
{
    const int thread_count = 2;
    thread ts[thread_count];
    for (int i=0; i<thread_count; i++)
    {
        ts[i] = thread(func);
    }
    for (auto& t : ts)
    {
        t.join();
    }
    wolfand11::Utility::AtomLog("MainThread %x :%d",this_thread::get_id(),value);
}

void time_mutex_test2(void(*func)(),int& value)
{
    thread t(func);
    this_thread::sleep_for(chrono::seconds(2));
    t.join();
    wolfand11::Utility::AtomLog("MainThread %x :%d",this_thread::get_id(),value);
}

void lock_guard_test1(void(*func)())
{
    const int thread_count = 5;
    thread ts[thread_count];
    for (int i=0; i<thread_count; i++)
    {
        ts[i] = thread(func);
    }
    for (auto& t : ts)
    {
        t.join();
    }
    wolfand11::Utility::AtomLog("MainThread %x :%d",this_thread::get_id());
}

void unique_lock_test1(void(*func)())
{
    const int thread_count = 10;
    thread ts[thread_count];
    for (int i=0; i<thread_count; i++)
    {
        ts[i] = thread(func);
    }
    for (auto& t : ts)
    {
        t.join();
    }
    wolfand11::Utility::AtomLog("MainThread %x :%d",this_thread::get_id());
}

// test func
void lesson3_test()
{
//    simple_mutex();
//    simple_mutex_1(accumulator_func_1);
//    simple_mutex_1(accumulator_func_1_1);
//    recursive_mutex_test();
//    time_mutex_test(accumulator_func_3,value_3);
//    time_mutex_test(accumulator_func_3_1,value_3_1);
//    time_mutex_test(accumulator_func_3_2, value_3_2);
//    time_mutex_test(accumulator_func_3_3, value_3_3);
//    time_mutex_test2(accumulator_func_3_3,value_3_3);
//    lock_guard_test1(print_id);
    unique_lock_test1(print_unique_lock_id);
}