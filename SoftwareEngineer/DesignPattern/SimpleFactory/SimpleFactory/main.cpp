#include <string>
#include <iostream>
#include "gitemfactory.h"

using namespace std;

struct Temp1
{
    virtual void SetA(char value){ a=value; }

    //virtual ~Temp1(){}
    char a;
private:
    char d;
public:
    int  c;
    char b;
};

class Temp2 :public Temp1
{
public:
    void SetE(char value){ e=value; }

    char e;
    char a;
};

int main(int argc, char* argv[])
{
    printf("127  = %X\n",127);
    printf("~127 = %X\n",~127);

    Temp1 temp1;
    char Temp1::*   temp1_a_P = 0;
    char Temp1::*   temp1_b_P = 0;
    int Temp1::*    temp1_c_P = 0;

    temp1_a_P = &Temp1::a;
    temp1_b_P = &Temp1::b;
    temp1_c_P = &Temp1::c;
    printf("temp1P_a %p\n",temp1_a_P);
    printf("temp1P_b %p\n",temp1_b_P);
    printf("temp1P_c %p\n",temp1_c_P);

    Temp2 temp2;
    char Temp2::* temp2_a_p = 0;
    temp2_a_p = &Temp2::a;
    printf("temp2P_a %p\n",temp2_a_p);

    void (Temp2::* SetAFunc)(char);
    SetAFunc = &Temp2::SetA;
    ( temp2.*SetAFunc )('A');
    printf("temp2P_SetAFunc %p\n",SetAFunc);
    printf("temp2.Temp1::a value = %c\n",temp2.Temp1::a);
    printf("temp2.Temp2::a value = %c\n",temp2.a);

    void (Temp2::* SetEFunc)(char);
    SetEFunc = &Temp2::SetE;
    ( temp2.*SetEFunc )('E');
    printf("temp2P_SetEFunc %p\n",SetEFunc);
    printf("temp2.e value = %c\n",temp2.e);

    GBaseItem* item = GItemFactory::GetInstance()->CreateItem(kItemType_AdItem);
    item->PrintType();
    return 0;
}









