#include "gdebug.h"
#include <QDebug>
#include <QOpenGLDebugMessage>

GDebug::GDebug()
    :_gl_logger(nullptr)
{
}

GDebug::~GDebug()
{
    if(_gl_logger)
    {
        delete _gl_logger;
    }
}

void GDebug::Init()
{
    _gl_logger = new QOpenGLDebugLogger(this);
    if(_gl_logger->initialize())
    {
        qDebug() << "GL_DEBUG Debug Logger" << _gl_logger << "\n";

        connect(_gl_logger, SIGNAL(messageLogged(QOpenGLDebugMessage)),this,SLOT(messageLogged(QOpenGLDebugMessage)));
        _gl_logger->startLogging();
    }
    else
    {
        qDebug() << "GL_DEBUG Debug Logger (NONE)\n";
    }
}

void GDebug::messageLogged(const QOpenGLDebugMessage &msg)
{
  QString error;

  // Format based on severity
  switch (msg.severity())
  {
  case QOpenGLDebugMessage::NotificationSeverity:
    error += "--";
    break;
  case QOpenGLDebugMessage::HighSeverity:
    error += "!!";
    break;
  case QOpenGLDebugMessage::MediumSeverity:
    error += "!~";
    break;
  case QOpenGLDebugMessage::LowSeverity:
    error += "~~";
    break;
  }

  error += " (";

  // Format based on source
#define CASE(c) case QOpenGLDebugMessage::c: error += #c; break
  switch (msg.source())
  {
    CASE(APISource);
    CASE(WindowSystemSource);
    CASE(ShaderCompilerSource);
    CASE(ThirdPartySource);
    CASE(ApplicationSource);
    CASE(OtherSource);
    CASE(InvalidSource);
  }
#undef CASE

  error += " : ";

  // Format based on type
#define CASE(c) case QOpenGLDebugMessage::c: error += #c; break
  switch (msg.type())
  {
    CASE(ErrorType);
    CASE(DeprecatedBehaviorType);
    CASE(UndefinedBehaviorType);
    CASE(PortabilityType);
    CASE(PerformanceType);
    CASE(OtherType);
    CASE(MarkerType);
    CASE(GroupPushType);
    CASE(GroupPopType);
  }
#undef CASE

  error += ")";
  qDebug() << qPrintable(error) << "\n" << qPrintable(msg.message()) << "\n";
}
