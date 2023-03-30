#ifndef TICKETINFO_H
#define TICKETINFO_H

#include <QString>
#include <QDate>
#include <QJsonObject>
#include <QDebug>
#include <src/tickets.h>

enum TicketStatus{Learned, Unlearned, Hard, Forgotten, Any};

class TicketInfo
{
private:
    static const int differenceOfAnswersForChangeToLearned = 5;
    static const int differenceOfAnswersForChangeStatuses = 3;

    int ticketIndex;
    TicketStatus status;

    int counterOfCorrectAnswers;
    int counterOfWrongAnswers;

    QDate dateOfLastAnswer;
    QDate dateOfStatusChanged;

    void changeStatus(TicketStatus status);

    void resetCounters();
    bool hasItBeenTwoWeeksFromLastAnswer();

public:
    TicketInfo(int index=0);

    static TicketInfo* createTicketInfo(QJsonObject ticketInfo);
    static TicketInfo* createTicketInfo(int index);

    static QString ticketStatusToQString(TicketStatus status);
    static TicketStatus qStringToTicketStatus(QString status);

    int getTicketIndex() const;   
    TicketStatus getTicketStatus() const;

    QDate getDateOfLastAnswer() const ;
    QDate getDateOfStatusChanged()const ;

    void saveAnswer(TicketAnswerType saveAnswer);
    void updateStatus();

    QJsonObject toJson();

    //debug
    void debugPrint()
    {
        qDebug() << "index: " << ticketIndex << ticketStatusToQString(status);
        qDebug() << "correct/wrong answ: " << counterOfCorrectAnswers << "/" << counterOfWrongAnswers;
        qDebug() << "last answ: " << dateOfLastAnswer.toString();
    }
};

#endif // TICKETINFO_H
