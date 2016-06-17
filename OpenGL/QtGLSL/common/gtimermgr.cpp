#include "gtimermgr.h"
#include "glhelper.h"

const uint32_t GTimerMgr::REPEAT_FOREVER = ~0;

GTimerMgr &GTimerMgr::GetInstance()
{
    static GTimerMgr _timer_mgr;
    return _timer_mgr;
}

void GTimerMgr::Schedule(QObject *target, std::function<void (float)> task, uint32_t count, float interval)
{
    TimerInfoMapIter iter = _target_timer_map.find(target);

    TimerInfoArr* timer_info_arr = nullptr;
    if(iter == _target_timer_map.end())
    {
        auto pair = _target_timer_map.insert(TimerInfoArrPair(target,TimerInfoArr()));
        timer_info_arr = &(pair.first->second);
    }
    else
    {
        timer_info_arr = &(iter->second);
    }
    GTimerInfo* timer_info = new GTimerInfo();
    timer_info_arr->push_back(timer_info);
    timer_info->task = task;
    timer_info->num  = count;
    connect(timer_info->timer, SIGNAL(timeout()), timer_info, SLOT(Update()));
    timer_info->timer->start(interval);
}

void GTimerMgr::Unschedule(QObject *target, std::function<void (float)> task)
{
    TimerInfoMapIter iter = _target_timer_map.find(target);

    if(iter != _target_timer_map.end())
    {
        TimerInfoArr& timer_info_arr = iter->second;
        for(TimerInfoArrIter info_arr_iter=timer_info_arr.begin(); info_arr_iter!=timer_info_arr.end();
            info_arr_iter++)
        {
            if(GLHelper::GetFuncAddr((*info_arr_iter)->task) == GLHelper::GetFuncAddr(task)
                    && (*info_arr_iter)->target == target)
            {
                timer_info_arr.erase(info_arr_iter);
                delete (*info_arr_iter);
            }
        }
    }
}

void GTimerMgr::OnScheduleCompleted(QObject* target,const QTimer* timer)
{
    TimerInfoMapIter iter = _target_timer_map.find(target);

    if(iter != _target_timer_map.end())
    {
        TimerInfoArr& timer_info_arr = iter->second;
        for(TimerInfoArrIter info_arr_iter=timer_info_arr.begin(); info_arr_iter!=timer_info_arr.end();
            info_arr_iter++)
        {
            if((*info_arr_iter)->timer->timerId() == timer->timerId())
            {
                timer_info_arr.erase(info_arr_iter);
                delete (*info_arr_iter);
                return;
            }
        }
    }
}

GTimerInfo::GTimerInfo()
    :count(0)
    ,num(0)
    ,target(nullptr)
    ,timer(nullptr)
    ,task(nullptr)
{
    timer = new QTimer();
}

GTimerInfo::~GTimerInfo()
{
    if(timer)
    {
        delete timer;
        timer = nullptr;
    }
}

void GTimerInfo::Update()
{
    count++;
    task(timer->interval());

    if(count>=num && num!=GTimerMgr::REPEAT_FOREVER)
    {
        timer->stop();
        GTimerMgr::GetInstance().OnScheduleCompleted(target,timer);
    }
}
