//
//  TheaterSimulator.h
//  ThreadTutorial
//
//  Created by guodong on 4/2/14.
//  Copyright (c) 2014 guodong. All rights reserved.
//
//  this example is from website:
//  http://www.chenlq.net/think-talk-write/c-pieces-her-to-listen-to-my-concert-a-random-number-in-c-11-the-thread-the-thread-mutual-exclusion-mutex-and-condition-variables-condition.html

#ifndef __ThreadTutorial__TheaterSimulator__
#define __ThreadTutorial__TheaterSimulator__

#include <iostream>
#include <queue>
#include <vector>
#include <random>
#include <thread>
#include <chrono>

// 观众，主要用来模拟检票过程中的检票耗费时间
class Viewer
{
public:
    void check()
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(400));
    }
    void arrival(int i)
    {
        std::this_thread::sleep_for(std::chrono::seconds(i));
    }
};

class Gate
{
public:
    Gate()
    {}
    
    void start(int n)
    {
        no_ = n;
        thread_ = std::thread(&Gate::Check,this);
    }
    
    void Check()
    {
        // 无限循环，直到观众数为0且不会有新的观众到来
        while (true)
        {
            
        }
    }
private:
    std::thread thread_;
    std::mutex  mutex_;
    std::condition_variable condition_var_;
    std::queue<Viewer>      viewer_queue_;
    int count_;
    int no_;
};

void RunTheaterSimulator();

#endif /* defined(__ThreadTutorial__TheaterSimulator__) */
