//
//  test.cpp
//  ThreadTutorial
//
//  Created by guodong on 4/2/15.
//  Copyright (c) 2015 guodong. All rights reserved.
//

#include <stdio.h>
#include <thread>
#include <sys/time.h>
using namespace std;

static int COUNT = 10;

void print_time(struct timeval& t1, struct timeval& t2, const char* msg)
{
    printf("%ld.%06d\t%s\n", t2.tv_sec-t1.tv_sec, t2.tv_usec-t1.tv_usec, msg);
}

void do_nothing(){}

void threadYield(void){
    unsigned int procs = thread::hardware_concurrency(), // 获取物理线程数目
    i = 0;
    thread* ta = new thread( [](){
        struct timeval t1, t2;
        gettimeofday(&t1, NULL);
        for(int i = 0, m = 13; i < COUNT; i++, m *= 17){
            this_thread::yield();
        }
        gettimeofday(&t2, NULL);
        print_time(t1, t2, " with yield");
    } );
    thread** tb = new thread*[ procs ];
    for( i = 0; i < procs; i++){
        tb[i] = new thread( [](){
            struct timeval t1, t2;
            gettimeofday(&t1, NULL);
            for(int i = 0, m = 13; i < COUNT; i++, m *= 17){
                do_nothing();
            }
            gettimeofday(&t2, NULL);
            print_time(t1, t2, "without yield");
        });
    }
    ta->join();
    delete ta;
    for( i = 0; i < procs; i++){
        tb[i]->join();
        delete tb[i];
    };
    delete tb;
}