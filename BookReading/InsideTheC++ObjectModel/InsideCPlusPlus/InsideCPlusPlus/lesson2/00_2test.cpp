//
//  00_test.cpp
//  InsideCPlusPlus
//
//  Created by Guo Dong on 7/12/16.
//  Copyright © 2016 Guo Dong. All rights reserved.
//

#include "00_2test.h"
#include "GHelper.h"

#pragma mark Test Nameed Return Value Optimization

const int test_arr_size = 100;
class test{
    friend test foo(double);
public:
    test()
    {
        printf("do default constructor\n");
        memset(array, 0, test_arr_size*sizeof(double));
    }
    inline test(const test& t)
    {
        printf("do copy constructor\n");
        memcpy(this, &t, sizeof(test));
    }
private:
    double array[test_arr_size];
};

test foo(double val)
{
    test local;
    local.array[0] = val;
    local.array[99] = val;
    int idx = 2;
    __asm {
        mov eax,idx   //comment this line out for RVO to kick in
        mov idx,eax   //comment this line out for RVO to kick in
    }
    local.array[idx] = val;
    return local;
}

void TestNamedReturnValueOp()
{
    const int obj_count = 10000;
    test obj_arr[obj_count];
    GCodeTimer::GetInstance().Reset();
    for(int cnt = 0; cnt<obj_count; cnt++)
    {
        obj_arr[cnt] = foo(double(cnt));
    }
    GCodeTimer::GetInstance().Record("NRV Op");
}

void TestLesson2(bool isRun)
{
    if(!isRun)return;
    
    TestNamedReturnValueOp();
}