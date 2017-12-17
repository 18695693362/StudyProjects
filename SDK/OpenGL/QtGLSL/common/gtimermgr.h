#ifndef GTIMERMGR_H
#define GTIMERMGR_H
#include <unordered_map>
#include <vector>
#include <QObject>
#include <QTimer>
#include <functional>
#include <utility>

class GTimerInfo;
class GTimerMgr: public QObject
{
    Q_OBJECT
public:
    static GTimerMgr& GetInstance();

    QTimer *Schedule(void *target, std::function<void(float)> task, uint32_t count, float interval);
    void Unschedule(void *target, QTimer *timer=nullptr);

    void OnScheduleCompleted(QObject* target, const QTimer *timer);

    static const uint32_t REPEAT_FOREVER;
private:
    typedef std::vector<GTimerInfo*> TimerInfoArr;
    typedef std::vector<GTimerInfo*>::iterator TimerInfoArrIter;
    typedef std::unordered_map< void*, TimerInfoArr > TimerInfoArrMap;
    typedef std::pair<void*,TimerInfoArr> TimerInfoArrPair;
    typedef TimerInfoArrMap::iterator TimerInfoMapIter;

    TimerInfoArrMap _target_timer_map;
};

class GTimerInfo: public QObject
{
    Q_OBJECT
public:
    GTimerInfo();
    ~GTimerInfo();

    QObject*                    target;
    QTimer*                     timer;
    std::function<void(float)>  task;
    uint32_t                    count;
    uint32_t                    num;
public slots:
    void Update();
};
#endif // GTIMERMGR_H
