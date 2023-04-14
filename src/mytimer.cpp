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
        currentTime.setHMS(0,0,0,0);

    oneSecTimer.start();
}

void MyTimer::Stop()
{

    oneSecTimer.stop();

    if(regime == TimerType::Timer)
        currentTime.setHMS(0,0,0,0);

}

void MyTimer::setRegime(TimerType regime)
{
    this->regime = regime;
}

void MyTimer::oneSecGone()
{
    if(regime == TimerType::Timer)
    {

     bool timeIsNull = (currentTime.hour()==0 && currentTime.minute()==0 && currentTime.second()==0);

    //если не проверять таймер на активность получается ситуация
    //последнее событие секунды вылетает - оно еще не дошло, а мы в это время сессию кончили
    //таймер остановили сделали ноль - срабатывает этот обработчик, видит нулевое время
    //АГА СУКА ВРЕМЯ ВЫЩЛА
    if(timeIsNull && oneSecTimer.isActive())
    {
        Stop();
        emit timeOut();
    }
    else
    {//если работаем как таймер но время еще не ноль
        currentTime = currentTime.addSecs(-1);
        emit timeUpdated();
    }
    }
    else if(oneSecTimer.isActive()){//если работаем как секундомер

      currentTime = currentTime.addSecs(+1);
      emit timeUpdated();
    }

}


