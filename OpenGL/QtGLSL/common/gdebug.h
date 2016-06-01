#ifndef GDEBUG_H
#define GDEBUG_H

#include <QOpenGLDebugLogger>
#include <QOpenGLDebugMessage>

class GDebug : public QObject
{
public:
    GDebug();
    ~GDebug();

    void Init();

protected slots:
    void messageLogged(const QOpenGLDebugMessage &msg);

private:
    QOpenGLDebugLogger* _gl_logger;
};

#endif // GDEBUG_H
