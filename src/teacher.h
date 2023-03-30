#ifndef TEACHER_H
#define TEACHER_H
#include <ticketbase.h>
#include <iostream>
#include <QTimer>
#include <QObject>

enum RepeatingTypes{onlyHardTickets, onlyForgotten, withTimer, randomTickets};

class Teacher: public QObject
{
 Q_OBJECT
private:
    TicketBase *ticketBase;

    QTimer timer;

    bool isTimeOut;

    void workOnTicket(Ticket *workedTicket);
    void workOnTicketList(QList <Ticket*> listOfTickets, bool withTimer = false);

    void repeatOnlyHardTickets(int amountOfTickets=10);
    void repeatOnlyForgotten(int amountOfTickets=10);
    void repeatWithTimer(int amountOfTickets=10);
    void repeatRandomTickets(int amountOfTickets=10);

private slots:
    void setTimeOut();

public:
    explicit Teacher(QObject *parent = nullptr);

    void setTicketBase(TicketBase *ticketBase);

    void learnTickets(int amountOfTickets=10);
    void repeatTickets(RepeatingTypes type, int amountOfTickets=10);
};

#endif // TEACHER_H
