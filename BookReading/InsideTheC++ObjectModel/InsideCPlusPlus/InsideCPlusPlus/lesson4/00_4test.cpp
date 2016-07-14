//
//  00_test.cpp
//  InsideCPlusPlus
//
//  Created by Guo Dong on 7/12/16.
//  Copyright © 2016 Guo Dong. All rights reserved.
//

#include "00_4test.h"
#include <iostream>
using namespace std;

class Point
{
public:
    Point(){}
    virtual ~Point(){}
    
    static void SPrint()
    {
        
    }
    virtual void VPrint()
    {
        cout << "Point::VPrint" << endl;
    }
    
    void Print()
    {
    }
    
    int x;
    int y;
};

class PointD :public Point
{
public:
    PointD(){}
    virtual void VPrint()
    {
        cout << "PointD::VPrint" << endl;
    }
};

void func0_lesson4(Point& point,void(Point::* print)())
{
    (point.*print)();
}
void test0_lesson4()
{
    PointD temp;
    func0_lesson4(temp, &Point::VPrint);
}

class L4_Base0
{
public:
    void Print()
    {
        VPrint();
    }
    virtual void VPrint()
    {
        printf("L4_Base0::VPrint\n");
    }
};
class L4_Drived0:public L4_Base0
{
public:
    virtual void VPrint()
    {
        printf("L4_Drived0::VPrint\n");
    }
};

void test1_lesson4()
{
    L4_Drived0 temp;
    L4_Base0& refTemp = temp;
    L4_Base0* ptrTemp = &temp;
    refTemp.Print();
    ptrTemp->Print();
}

void TestLesson4(bool isRun)
{
    if(!isRun)return;
    
    printf("Point::SPrint  = %p\n", &Point::SPrint);
    //printf("Point::Point = %p\n", &Point::Point);
    //printf("Point::~Point = %p\n", &Point::~Point);
    printf("Point::Print   = %p\n", &Point::Print);
    printf("Point::VPrint  = %p\n", &Point::VPrint);
    printf("PointD::VPrint = %p\n", &PointD::VPrint);
    
    test0_lesson4();
    test1_lesson4();
}









