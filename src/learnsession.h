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
    const int ticketsInOneSession = 1;
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

    int getCountRight() const;
    int getCountWrong() const;
    QList <Ticket*> getListOfWrongTicket();

    QTime getSessionLasting() const;


signals:
    void pushListOfTickets(QList <Ticket*> listOfTickets, QString finalScreen);
    void learnSessionStatisticChanged();
    void learnSessionLastingTimeChanged();

public slots:
    //void saveStatisticInLearningSession(int index, bool isCorrect);
    void onSaveStatisticInLearningSession(int index, TicketAnswerType correcness);
    void onStartLearningFailedTickets();

    void onLastingTimerChanged();
};

#endif // LEARNSESSION_H
