//
//  Promise.cpp
//  ThreadTutorial
//
//  Created by guodong on 4/3/14.
//  Copyright (c) 2014 guodong. All rights reserved.
//

#include "Promise.h"
#include <thread>
#include <functional>
#include <future>
#include <iostream>
#include <chrono>

using namespace std;

void thread_function_print_int(future<int>& future_value)
{
    int x = future_value.get();
    cout << __FUNCTION__ << ": future_value=" << x << "\n";
}

void TestPromise()
{
    promise<int>    promise_obj;
    future<int>     future_obj = promise_obj.get_future();
    thread thread_1(thread_function_print_int,ref(future_obj));
    promise_obj.set_value(10); // 设置共享状态的值，此处和线程thread_1保持同步
    
    thread_1.join();
}

void thread_function_input_int(promise<int>& promise_arg)
{
    int temp;
    cout << "Please, enter an integer value: ";
    std::cin.exceptions(std::ios::failbit);
    try
    {
        std::cin >> temp;
        promise_arg.set_value(temp);
    }
    catch (std::exception&)
    {
        promise_arg.set_exception(std::current_exception());
    }
}

void thread_function_output_int(future<int>& future_arg)
{
    try
    {
        int temp = future_arg.get();
        cout << "value: " << temp << "\n";
    }
    catch (std::exception& e)
    {
        cout << "[exception caught: ]" << e.what() << "]\n";
    }
}

void TestPromiseException()
{
    promise<int>    promise_obj;
    future<int>     future_obj = promise_obj.get_future();
    
    std::thread thread_1(&thread_function_input_int,ref(promise_obj));
    std::thread thread_2(thread_function_output_int,ref(future_obj));
    
    thread_1.join();
    thread_2.join();
}

int thread_function_countdown(int from, int to)
{
    for (int i=from; i!=to; i--)
    {
        std::cout << i << "\n";
        this_thread::sleep_for(chrono::seconds(1));
    }
    std::cout << "Finished\n";
    return from-to;
}

void TestPackagedTask1()
{
    packaged_task<int(int,int)> temp_packaged_task(&thread_function_countdown);
    future<int> temp_future = temp_packaged_task.get_future();
    
    thread temp_thread(std::move(temp_packaged_task), 10, 0);
    int return_value = temp_future.get();
    
    cout << "The countdown lasted for " << return_value << " seconds.\n";
    temp_thread.join();
}

void TestPackagedTask2()
{
    std::packaged_task<int(int,int)> default_packaged_task;
    std::packaged_task<int(int,int)> lambda_packaged_task([](int from,int to)->int
                                                          {
                                                              return from-to;
                                                          });
    if (!default_packaged_task.valid())
    {
        cout << "default_packaged_task is invalid!\n";
    }
    default_packaged_task = move(lambda_packaged_task);
    if (default_packaged_task.valid())
    {
        cout << "default_packaged_task is   valid! (after move operator)\n";
    }
    future<int> return_future = default_packaged_task.get_future();
    
    thread(std::move(default_packaged_task), 10, 0).detach();
    
    int return_value = return_future.get();
    cout << "return value is " << return_value << ".\n";
}






