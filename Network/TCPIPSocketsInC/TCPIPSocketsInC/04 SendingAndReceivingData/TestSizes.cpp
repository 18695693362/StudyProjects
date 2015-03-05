//
//  TestSizes.cpp
//  TCPIPSocketsInC
//
//  Created by Guo Dong on 3/5/15.
//  Copyright (c) 2015 guodong. All rights reserved.
//

#include "TestSizes.h"
#include <stdint.h>
#include <iostream>

using namespace std;

void Test04_TestSizes(bool is_run)
{
    if (!is_run)
    {
        return;
    }
    
    int8_t  int8_value  = -30;
    int16_t int16_value = int8_value;
    printf("int8_value  : %x\n",int8_value);
    printf("int16_value : %x\n",int16_value);
    printf("int8_value  : %d\n",int8_value);
    printf("int16_value : %d\n",int16_value);
}