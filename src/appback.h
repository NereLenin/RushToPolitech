#ifndef APPBACK_H
#define APPBACK_H
#include <QObject>
#include <QList>

#include <tickets.h>
#include <ticketsdatabasereader.h>

class appBack : public QObject
{
    Q_OBJECT
public:
    explicit appBack(QObject *parent = nullptr);

    void readTicketsFromDB();
    void setPathToTicketsDB(QString pathToTicketDB);

    void printTicket(int index);
    void askTicket(const Ticket& ticket);

    void learnTickets();

    //repeat tickets
    void repeatHardTickets();
    void repeatWithTime();
    void repeatRandomTickets();
    void repeatForgottenTickets();

    //exam
    void tryExam();

signals:

private:
    QString pathToTicketDB;
    QList<Ticket*> tickets;

    void clearTickets();
};

#endif // APPBACK_H
