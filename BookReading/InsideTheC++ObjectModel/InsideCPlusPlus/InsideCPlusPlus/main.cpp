#include <iostream>
#include "lesson1/00_1test.h"
#include "lesson2/00_2test.h"
#include "lesson3/00_3test.h"
#include "lesson4/00_4test.h"
#include "lesson5/00_5test.h"
#include "lesson6/00_6test.h"
#include "lesson7/00_7test.h"
using namespace std;

//extern void TestLesson6(bool);
void TestLesson6(bool);
//extern int l6_ivalue;

void test_type_cast()
{
    const int temp_01 = 10;
    //    int temp_02 = const_cast<int>(temp_01);               //编译出错
    //    cout << "temp_02 = " << temp_02 << endl;
    
    int temp_11 = 10;
//        const int temp_12 = const_cast<const int>(temp_11);   //编译出错
//        cout << "temp_12 = " << temp_12 << endl;
    
    const int* temp_21 = &temp_01;
    int* temp_22 = const_cast<int*>(temp_21);
    cout << "temp_22 = " << temp_22 << endl;
    
    int* temp_31 = &temp_11;
    const int* temp_32 = const_cast<const int*>(temp_31);
    cout << "temp_32 = " << temp_32 << endl;
}

int main(int argc, char *argv[])
{
    cout << "Hello World!" << endl;
    TestLesson1(true);
    //TestLesson2(true);
    //TestLesson3(true);
    //TestLesson4(true);
    //TestLesson5(true);
    TestLesson6(true);
    //TestLesson7(true);
    
    //cout << "l6_static_ivalue = " << l6_static_ivalue << endl;
    
    extern int l6_global_ivalue;
    cout << "l6_global_ivalue = " << l6_global_ivalue << endl;
    
    test_type_cast();
    return 0;
}













