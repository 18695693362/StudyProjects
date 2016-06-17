#include "gtimermgr.h"

GTimerMgr &GTimerMgr::GetInstance()
{
    static GTimerMgr _timer_mgr;
    return _timer_mgr;
}

GTimerMgr::GTimerMgr()
{

}

void GTimerMgr::schedule(QObject *target, std::function<void (float)> task, float count, float interval)
{
}
