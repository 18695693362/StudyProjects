//
//  HelloWorld.cpp
//  ThreadTutorial
//
//  Created by guodong on 9/30/14.
//  Copyright (c) 2014 guodong. All rights reserved.
//

#include "HelloWorld.h"
#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

void PrintHelloWorld()
{
    cout << "HelloWorld" << endl;
}

void lesson1_HelloWorld()
{
    thread empty_thread;
    
    thread thread1(PrintHelloWorld);
    if (thread1.joinable())
    {
        // comment this line will invoke error
        cout << "before sleep" << endl;
        this_thread::sleep_for(chrono::seconds(2));
        cout << "after sleep" << endl;
        thread1.join();
        // after invoke join(), the thread isn't joinable
        //thread1.join();
    }
}

void lesson1_test()
{
    lesson1_HelloWorld();
}