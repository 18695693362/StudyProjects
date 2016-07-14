#ifndef GVFUNC_H
#define GVFUNC_H

#include <iostream>
#include <string>

class GVFuncBase1
{
    virtual ~GVFuncBase1()
    {
        std::cout << "~GVFuncBase1" << std::endl;
    }
    virtual void PrintI(int iValue)
    {
        std::cout << "GVFuncBase1::iValue = " << iValue << std::endl;
    }
    virtual void PrintS(std::string sValue)
    {
        std::cout << "GVFuncBase1::sValue = " << sValue << std::endl;
    }
};

class GVFunc
{
public:
    GVFunc();
    virtual ~GVFunc()
    {
        std::cout << "~GVFunc" << std::endl;
    }
    virtual void PrintI(int iValue)
    {
        std::cout << "GVFunc::iValue = " << iValue << std::endl;
    }
    virtual void PrintS(std::string sValue)
    {
        std::cout << "GVFunc::sValue = " << sValue << std::endl;
    }
    int value;
};

#endif // GVFUNC_H
