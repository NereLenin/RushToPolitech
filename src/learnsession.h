#ifndef LEARNSESSION_H
#define LEARNSESSION_H
#include <QObject>
#include <QQmlEngine>//?

#include "ticketbase.h"
#include "mytimer.h"
#include "theory/topic.h"



class LearnSession : public QObject
{
    Q_OBJECT
public:
    enum TypeLearning{DefaultLearning, RepeatHard, RepeatWithTimer,
                      RepeatRandom, RepeatForgotten, Exam, LearnFailedFromRepeat,
                      LearnFailedFromLearnOrExam, LearnTicketsInTopic};
    Q_ENUMS(TypeLearning)

    static void initializeTypeLearningForQml(){
        qmlRegisterType<LearnSession>("TypeLearning",0,1,"LearnType");
    }
private:
    const int ticketsInOneSession = 10;
    const int timeToFinishSessionInMinutes = 5;

    const int ticketsInExamSession = 40;
    const int examTime = 15;

    int currentLearnedTicketNumber;

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

    void learnTicketsInSubtopic(const Subtopic *subtopic){
        qDebug() << "LearnSession::learnTicketsInTopic";
        if(subtopic == nullptr)
        {
            qDebug() << "LS: learnTicketsInTopic try to learn null topic";
            return;
        }

        QList<Ticket*> topicTickets;

            for(int i = 0; i < subtopic->getTicketAnswers().size(); i++)
            {
            Ticket *currentSubtopicTicket = base->getTicket(subtopic->getTicketAnswers()[i].getTicketIndex());

            if(currentSubtopicTicket != nullptr)
                topicTickets.append(currentSubtopicTicket);
            }

        if(topicTickets.size() > 0)
            pushListOfTickets(topicTickets);
    }


    void ExamSession();

    void saveTicketInList(Ticket* ticket);

    explicit LearnSession(QObject *parent = nullptr);
public:

    static LearnSession* createSession(TicketBase *ticketBase, TypeLearning regime);

    void StartSession();

    Subtopic *currentLearnedSubtopic;

    TypeLearning getCurrentRegime() const;

    int getCountRight() const;
    int getCountWrong() const;

    int getCurrentTicketNumber() const;
    int getCountOfTicketsInSession() const;

    QList <Ticket*> getListOfWrongTicket();

    QTime getSessionLasting() const;
    QTime getTimerTime() const;

    ~LearnSession(){
        qDebug() << "LS destructor";
    }

    void setCurrentLearnedSubtopic(Subtopic *newCurrentLearnedTopic);

signals:
    void pushListOfTickets(QList <Ticket*> listOfTickets);
    void pushFinalScreen();

    void learnSessionStatisticChanged();
    void learnSessionTimeChanged();
public slots:

    void onSaveStatisticInLearningSession(int index, TicketAnswerType correcness);
    void onStartLearningFailedTickets();

    void onTimeChanged();
    void onTimerTimeOut();

    void onFinishSession();
};

#endif // LEARNSESSION_H
