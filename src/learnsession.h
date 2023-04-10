#ifndef LEARNSESSION_H
#define LEARNSESSION_H
#include <src/ticketbase.h>
#include <src/mytimer.h>

#include <QObject>

enum TypeLearning{DefaultLearning, RepeatHard,RepeatWithTimer,RepeatRandom,RepeatForgotten,Exam};

class LearnSession : public QObject
{
    Q_OBJECT
private:
    const int ticketsInOneSession = 10;
    const int timeToFinishSessionInMinutes = 5;

    const int ticketsInExamSession = 40;
    const int examTime = 20;

    TypeLearning currentRegime;

    int countOfRightAnswer;
    int countOfWrongAnswer;

    MyTimer sessionLasting;

    MyTimer timer;

    QVariant modlelListOfWrongTickets;

    QList <Ticket*> listOfWrongTickets;
    TicketBase *base;

    void defaultLearnSession();

    void repeatHardSession();
    void repeatWithTimerSession();
    void repeatRandomSession();
    void repeatForgottenSession();

    void learnFailedTicketsSession();

    void ExamSession();

    void saveTicketInList(Ticket* ticket);

    explicit LearnSession(QObject *parent = nullptr);
public:

    static LearnSession* createSession(TicketBase *ticketBase, TypeLearning regime);

    void StartSession();

    TypeLearning getCurrentRegime() const;
    int getCountRight() const;
    int getCountWrong() const;
    QList <Ticket*> getListOfWrongTicket();

    QTime getSessionLasting() const;
    QTime getTimerTime() const;

signals:
    void pushListOfTickets(QList <Ticket*> listOfTickets);
    void pushFinalScreen();

    void learnSessionStatisticChanged();
    void learnSessionLastingTimeChanged();
public slots:

    void onSaveStatisticInLearningSession(int index, TicketAnswerType correcness);
    void onStartLearningFailedTickets();

    void onLastingTimerChanged();//переименовать просто в time changed
    void onTimerTimeOut();

    void onFinishSession();
};

#endif // LEARNSESSION_H
