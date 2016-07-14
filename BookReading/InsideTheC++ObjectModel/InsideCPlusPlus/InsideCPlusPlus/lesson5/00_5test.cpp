//
//  00_test.cpp
//  InsideCPlusPlus
//
//  Created by Guo Dong on 7/12/16.
//  Copyright © 2016 Guo Dong. All rights reserved.
//

#include "00_5test.h"

class L5_Point
{
public:
    inline L5_Point(float x,float y)
    :x_(x)
    ,y_(y)
    {}
    inline float x()
    {
        return x_;
    }
private:
    float x_;
    float y_;
};

void TestLesson5(bool isRun)
{
    L5_Point point = {1,2};
    printf("point x = %f\n",point.x());
}