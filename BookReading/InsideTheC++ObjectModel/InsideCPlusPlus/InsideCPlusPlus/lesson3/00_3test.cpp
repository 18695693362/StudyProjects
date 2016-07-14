//
//  00_test.cpp
//  InsideCPlusPlus
//
//  Created by Guo Dong on 7/12/16.
//  Copyright © 2016 Guo Dong. All rights reserved.
//

#include "00_3test.h"

class Point3d {
    
public:
    static void Print()
    {
        printf("&Point3d::x = %d\n", &Point3d::x);
        printf("&Point3d::y = %d\n", &Point3d::y);
        printf("&Point3d::z = %d\n", &Point3d::z);
    }
    virtual ~Point3d(){}
protected:
    static Point3d origin;
    float x,y,z;
};

class VBase
{
public:
    int vbase;
};
class Type1:virtual public VBase
{
public:
    int type1;
};
class Type2:virtual public VBase
{
public:
    int type2;
};
class Type:public Type1,public Type2
{
public:
    static void Print()
    {
        
        
        printf("sizeof(int)   = %lu\n", sizeof(int));
        printf("&VBase::vbase = %d\n", &VBase::vbase);
        
        printf("&Type1::type1 = %d\n", &Type1::type1);
        printf("&Type1::vbase = %d\n", &Type1::vbase);
        
        printf("&Type2::type2 = %d\n", &Type2::type2);
        printf("&Type2::vbase = %d\n", &Type2::vbase);
        
        printf("&Type::type  = %d\n", &Type::type);
        printf("&Type::type1 = %d\n", &Type::type1);
        printf("&Type::type2 = %d\n", &Type::type2);
        printf("&Type::vbase = %d\n", &Type::vbase);
    }
    int type;
};
int func1(int Type::*typeMemberPointer, Type* typePtr)
{
    return typePtr->*typeMemberPointer;
}
int func2(Type* typePtr)
{
    //int Type2::*memberPointer = &Type2::type2;
    int Type1::*memberPointer = &Type1::type1;
    return func1(memberPointer,typePtr);
}
void test0_lesson3()
{
    Type temp;
    temp.vbase = 1;
    temp.type1 = 2;
    temp.type2 = 3;
    temp.type  = 4;
    printf("func1-func2 result = %d\n",func2(&temp));
}
void TestLesson3(bool isRun)
{
    if(!isRun)return;
    Point3d::Print();
    Type::Print();
    test0_lesson3();
}