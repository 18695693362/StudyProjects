//
//  thread_study.cpp
//  ThreadTutorial
//
//  Created by guodong on 9/30/14.
//  Copyright (c) 2014 guodong. All rights reserved.
//

#include "thread_study.h"
#include <thread>
#include <iostream>
#include <string>

using namespace std;

// thread func

void print_hw()
{
    cout << "SubThread:HelloWorld" << endl;
}

void print_arg_str_value(string arg)
{
    cout << "SubThread:" << arg << endl;
}

void print_arg_str_ref(string& arg)
{
    cout << "SubThread:" << arg << endl;
    arg += "_changed";
}

void print_arg_int_value(int arg)
{
    cout << "SubThread("<< this_thread::get_id() <<"):" << arg << endl;
}

// thread creator

void thread_create_default()
{
    thread default_t;
    if(default_t.joinable())
    {
        cout << "default thread is joinable" << endl;
    }
    else
    {
        cout << "default thread isn't joinable" << endl;
    }
}

void thread_create_pass_value()
{
    string str("StrValue");
    thread t(print_arg_str_value,str);
    t.join();
}

void thread_create_pass_ref()
{
    string str("StrRef");
    thread t(print_arg_str_ref,ref(str));
    t.join();
    cout << "MainThread:" << str << endl;
}

void thread_create_move()
{
    thread t1(print_hw);
    thread t2(std::move(t1));
    if (t1.joinable())
    {
        t1.join();
        cout << "thread_create_move:t1 is joinable" << endl;
    }
    else
    {
        cout << "thread_create_move:t1 isn't joinable" << endl;
    }
    if (t2.joinable())
    {
        t2.join();
        cout << "thread_create_move:t2 is joinable" << endl;
    }
    else
    {
        cout << "thread_create_move:t2 isn't joinable" << endl;
    }
}

void thread_move_copy()
{
    thread ts[6];
    for (int i=0; i<5; i++)
    {
        ts[i] = thread(print_arg_int_value,i);
    }
    
    //runtime error: thread move copy error,because ts[0].joinable() == true
    //ts[0] = thread(print_arg_int_value,-1);
    
    //compile error: thread default copy is invalid
    //ts[5] = ts[4];
    
    for (int i=0; i<5; i++)
    {
        ts[i].join();
    }
}

// test
void lesson2_test()
{
//    thread_create_default();
//    thread_create_pass_value();
//    thread_create_pass_ref();
//    thread_create_move();
    thread_move_copy();
}
