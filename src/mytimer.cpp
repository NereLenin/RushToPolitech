#include "mytimer.h"

MyTimer::MyTimer(QObject *parent)
    : QObject{parent}
{
    oneSecTimer.setInterval(1000);
    QObject::connect(&oneSecTimer, &QTimer::timeout, this, &MyTimer::oneSecGone);
    regime = TimerType::Timer;
}

void MyTimer::setTime(QTime waitingTime)
{
    currentTime = waitingTime;
}

QTime MyTimer::getCurrentTime() const
{
    return currentTime;
}

void MyTimer::Start()
{
    if(regime == TimerType::Stopwatch)
        currentTime = QTime::fromString("00:00:00");

    oneSecTimer.start();
}

void MyTimer::Stop()
{
    if(regime == TimerType::Timer)
        currentTime = QTime::fromString("00:00:00");

    oneSecTimer.stop();
}

void MyTimer::setRegime(TimerType regime)
{
    this->regime = regime;
}

void MyTimer::oneSecGone()
{
    if(regime == TimerType::Timer)
    {
    if(currentTime.hour()==0 && currentTime.minute()==0 && currentTime.second()==0)
    {
        Stop();
        emit timeOut();
    }
    else
    {
        currentTime = currentTime.addSecs(-1);
        emit timeUpdated();//currentTime);
    }
    }
    else{
      currentTime = currentTime.addSecs(+1);
      emit timeUpdated();//currentTime);
    }

}


