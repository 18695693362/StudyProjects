//
//  00_test.cpp
//  InsideCPlusPlus
//
//  Created by Guo Dong on 7/12/16.
//  Copyright © 2016 Guo Dong. All rights reserved.
//

#include "00_6test.h"
#include <iostream>
using namespace std;

class L6_Test00
{
public:
    L6_Test00()
    {
        cout << "L6_Test00 -- L6_Test00()" << endl;
    }
    L6_Test00(int a)
    {
        m_value = a;
        cout << "L6_Test00 -- L6_Test00(int a)" << endl;
    }
    static void Print()
    {
        cout << "L6_Test00::Print" << endl;
    }
    static int ivalue;
    static float fvalue;
    
    int m_value;
};
int L6_Test00::ivalue;
float L6_Test00::fvalue = 2.0;
static L6_Test00 l6_obj1;
L6_Test00 l6_obj2(3);

static int l6_static_ivalue = 10;
int l6_global_ivalue = 11;
static const int l6_static_const_ivalue = 12;
void l6_test00()
{
//#define TEST_LOCAL_EXTERN
#ifdef TEST_LOCAL_EXTERN
    extern int iValue1 = 10; // 报错
    int iValue2 = 11;
    extern int iValue2;      // 报错
    extern int iValue3;
    int iValue3;             // 报错
#endif
}

class L6_Point_01 {
public:
    L6_Point_01()
    {
        cout << "L6_Point_01()" << endl;
    }
    virtual ~L6_Point_01()
    {
        cout << "~L6_Point_01()" << endl;
    }
};
class L6_Point3d_01: public L6_Point_01
{
public:
    L6_Point3d_01()
    {
        cout << "L6_Point3d_01()" << endl;
    }
    ~L6_Point3d_01()
    {
        cout << "~L6_Point3d_01()" << endl;
    }
};
void l6_test01()
{
    L6_Point_01* ptr = new L6_Point3d_01[3];
    delete [] ptr;
}

class L6_Test_02 {
public:
    L6_Test_02(string name)
    {
        this->name = name;
        cout << "L6_Test_02() name = " << this->name << endl;
    }
    virtual ~L6_Test_02()
    {
        cout << "~L6_Test_02()" << this->name << endl;
    }
    string name;
};
L6_Test_02 operator+(const L6_Test_02& lhs, const L6_Test_02& rhs)
{
    L6_Test_02 temp("0");
    temp.name = lhs.name+"+"+rhs.name;
    return temp;
}


void l6_test02()
{
    cout << "l6_test02-begin" << endl;
    L6_Test_02 temp1("test1");
    L6_Test_02 temp2("test2");
    L6_Test_02 temp3("test3");
    temp3 = temp1 + temp2;
    temp1.name = "real-temp1";
    temp2.name = "real-temp2";
    temp3.name = "real-temp3";
    cout << "l6_test02-end" << endl;
}

void TestLesson6(bool isRun)
{
    if(!isRun) return;
    
    cout << "L6_Test00::ivalue = " << L6_Test00::ivalue << endl;
    cout << "L6_Test00::fvalue = " << L6_Test00::fvalue << endl;
    static L6_Test00 temp;
    L6_Test00::ivalue = 10;
    cout << "L6_Test00::ivalue = " << L6_Test00::ivalue << endl;
    temp.ivalue = 20;
    cout << "L6_Test00::ivalue = " << L6_Test00::ivalue << endl;
    
    cout << "l6_obj1.m_value = " << l6_obj1.m_value << endl;
    cout << "l6_obj2.m_value = " << l6_obj2.m_value << endl;
    L6_Test00::Print();
    
    //cout << "l_ivalue = " << l_ivalue << endl;
    
    l6_test01();
    l6_test02();
}