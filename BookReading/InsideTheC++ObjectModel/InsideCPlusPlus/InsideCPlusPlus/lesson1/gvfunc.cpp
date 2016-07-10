#include "gvfunc.h"
#include "GHelper.h"
using namespace std;

GVFunc::GVFunc()
{

}

void TestLesson1(bool isRun)
{
    if(!isRun)return;
    GVFunc vfunc1;
    cout << (void*)&vfunc1 << endl;
    GVFunc* pVFunc = &vfunc1;
    cout << (void*)(pVFunc+1)<< endl;
    
    //void* pVFuncAddr = reinterpret_cast<void*>(GVFunc::Print);
    //cout << pVFuncAddr << endl;
    cout << GHelper::MemberFuncToString(&GVFunc::PrintI) << endl;
    cout << GHelper::MemberFuncToString(&GVFunc::PrintS) << endl;
    cout << &GVFunc::PrintS << endl;
    
    typedef void (*PPrintFunc)(GVFunc*,int);
    char* pVTable = (char*)(pVFunc+1);
    PPrintFunc pPrintFunc = (PPrintFunc)(pVTable+1);
    pPrintFunc(pVFunc, 10);
}
