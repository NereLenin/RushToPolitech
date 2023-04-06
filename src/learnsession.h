#ifndef LEARNSESSION_H
#define LEARNSESSION_H
#include <src/ticketbase.h>

#include <QObject>

enum TypeLearning{DefaultLearning, RepeatHard,RepeatWithTimer,RepeatRandom,RepeatForgotten,Exam};

class LearnSession : public QObject
{
    Q_OBJECT
private:
    const int ticketsInOneSession = 10;
    TypeLearning currentRegime;

    int countOfRightAnswer;
    int countOfWrongAnswer;

    QTime sessionLastTime;//переименовать
    QVariant modlelListOfWrongTickets;

    QList <const Ticket*> listOfWrongTickets;
    TicketBase *base;

    void defaultLearnSession();

    void repeatHardSession();
    void repeatWithTimerSession();
    void repeatRandomSession();
    void repeatForgottenSession();

    void ExamSession();

    explicit LearnSession(QObject *parent = nullptr);
public:

    static LearnSession* createSession(TicketBase *ticketBase, TypeLearning regime);

    void StartSession();

signals:
    void pushListOfTickets(QList <Ticket*> listOfTickets, QString finalScreen);

public slots:
    //void saveStatisticInLearningSession(int index, bool isCorrect);
    void onSaveStatisticInLearningSession(int index, TicketAnswerType correcness);
};

#endif // LEARNSESSION_H
