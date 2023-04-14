#ifndef MYTIMER_H
#define MYTIMER_H

#include <QObject>
#include <QTimer>
#include <QTime>

enum TimerType {Timer, Stopwatch};

class MyTimer : public QObject
{
    Q_OBJECT

private:
    QTime currentTime;
    QTimer oneSecTimer;

    TimerType regime;

public:
    explicit MyTimer(QObject *parent = nullptr);

    void setTime(QTime waitingTime);
    void setTime(int m,int s, int ms = 0);

    QTime getCurrentTime() const;

    void Start();
    void Stop();

    void setRegime(TimerType regime);

signals:
    void timeOut();
    void timeUpdated();

private slots:
    void oneSecGone();
};

#endif // MYTIMER_H
