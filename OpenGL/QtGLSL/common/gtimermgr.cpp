#include "gtimermgr.h"
#include "glhelper.h"

using namespace std;

const uint32_t GTimerMgr::REPEAT_FOREVER = ~0;

GTimerMgr &GTimerMgr::GetInstance()
{
    static GTimerMgr _timer_mgr;
    return _timer_mgr;
}

QTimer* GTimerMgr::Schedule(void *target, std::function<void (float)> task, uint32_t count, float interval)
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
    return timer_info->timer;
}

void GTimerMgr::Unschedule(void *target, QTimer* timer)
{
    TimerInfoMapIter iter = _target_timer_map.find(target);

    if(iter != _target_timer_map.end())
    {
        TimerInfoArr& timer_info_arr = iter->second;
        GLHelper::Log(string("size = ")+to_string(timer_info_arr.size()));
        for(TimerInfoArrIter info_arr_iter=timer_info_arr.begin(); info_arr_iter!=timer_info_arr.end();)
        {
            if( timer && timer != (*info_arr_iter)->timer )
            {
                info_arr_iter++;
                continue;
            }
            info_arr_iter = timer_info_arr.erase(info_arr_iter);
            delete (*info_arr_iter);
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
    :QObject()
    ,count(0)
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
