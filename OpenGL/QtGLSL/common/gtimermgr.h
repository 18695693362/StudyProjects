#ifndef GTIMERMGR_H
#define GTIMERMGR_H
#include <unordered_map>
#include <QTimer>
#include <functional>

class GTimerMgr
{
public:
    static GTimerMgr& GetInstance();

    GTimerMgr();

    void schedule(QObject* target,std::function<void(float)> task,float count, float interval);
    void unschedule(QObject* target,std::function<void(float)> task=nullptr);
private:
    struct TimerInfo {
        QTimer*                     timer;
        std::function<void(float)>  task;
    };
    std::unordered_map<QObject*,TimerInfo*> _target_timer_map;
};

#endif // GTIMERMGR_H
