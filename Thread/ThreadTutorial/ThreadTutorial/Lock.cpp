//
//  Lock.cpp
//  ThreadTutorial
//
//  Created by guodong on 4/3/14.
//  Copyright (c) 2014 guodong. All rights reserved.
//

#include "Lock.h"
#include <thread>
using namespace std;

/**
 lock_guard
 */
mutex lock_guard_mutex;

void print_even(int value)
{
    string character = value%2==0 ? "e" : "o";
    for (int i=0; i<50; i++)
    {
        cout << character;
    }
    cout << "\n";
    
    if (value%2==0) {
        cout << value << " is even\n";
    }
    else
    {
        throw(logic_error("not even"));
    }
}

void thread_function_print_value(int value)
{
    try
    {
        lock_guard<std::mutex> lock_guard(lock_guard_mutex);
        print_even(value);
    }
    catch (logic_error&)
    {
        cout << "[exception caught]\n";
    }
}

void thread_function_print_value_adopt_lock(int value)
{
    try
    {
        lock_guard_mutex.lock();
        lock_guard<std::mutex> lock_guard(lock_guard_mutex,
                                          adopt_lock);
        print_even(value);
    }
    catch (logic_error&)
    {
        cout << "[exception caught]\n";
    }
}

void TestLockGuard()
{
    std::thread threads[5];
    for (int i=0; i<5; i++)
    {
        threads[i] = thread(thread_function_print_value,i);
    }
    for (auto& temp : threads)
    {
        temp.join();
    }
}

void TestLockGuardAdoptLock()
{
    std::thread threads[5];
    for (int i=0; i<5; i++)
    {
        threads[i] = thread(thread_function_print_value_adopt_lock,i);
    }
    for (auto& temp : threads)
    {
        temp.join();
    }
}

/**
 unique lock
 */
mutex mutex_for_unique_lock;
void thread_function_for_unique_lock(int n, char c)
{
    unique_lock<mutex> temp_unique_lock(mutex_for_unique_lock);
    for (int i=0; i<n; i++)
    {
        cout << c;
    }
    cout << '\n';
}

void TestUniqueLock()
{
    thread thread1 = thread(thread_function_for_unique_lock,50,'*');
    thread thread2 = thread(thread_function_for_unique_lock,50,'$');
    
    thread1.join();
    thread2.join();
}

mutex mutex_for_unique_lock_1;
mutex mutex_for_unique_lock_2;
void thread_function_for_unique_lock_1()
{
    lock(mutex_for_unique_lock_1, mutex_for_unique_lock_2);
    unique_lock<std::mutex> unique_lock_1(mutex_for_unique_lock_1,
                                          std::adopt_lock);
    unique_lock<std::mutex> unique_lock_2(mutex_for_unique_lock_2,
                                          std::adopt_lock);
    cout << __FUNCTION__ << "\n";
}

void thread_function_for_unique_lock_2()
{
    unique_lock<mutex> unique_lock_1,unique_lock_2;
    unique_lock_1 = unique_lock<mutex>(mutex_for_unique_lock_1,
                                       std::defer_lock);
    unique_lock_2 = unique_lock<mutex>(mutex_for_unique_lock_2,
                                       std::defer_lock);
    lock(mutex_for_unique_lock_1, mutex_for_unique_lock_2);
    
    cout << __FUNCTION__ << "\n";
}

void TestCreateUniqueLock1()
{
    thread thread_1(thread_function_for_unique_lock_1);
    thread thread_2(thread_function_for_unique_lock_2);
    thread_1.join();
    thread_2.join();
}














