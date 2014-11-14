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

using namespace std;

void PrintHelloWorld()
{
    cout << "HelloWorld" << endl;
}

void lesson1_HelloWorld()
{
    thread thread1(PrintHelloWorld);
    thread1.join();
}

void lesson1_test()
{
    lesson1_HelloWorld();
}