#ifndef TICKETBASE_H
#define TICKETBASE_H
#include "ticketsdatabasereader.h"
#include "ticketsstatisticservice.h"

class TicketBase : public ITicketStatistic
{
private:
    QList <Ticket*> ticketsBase;
    double baseVersion;

    TicketsStatisticService statistic;

    QString pathToStatisticBase;
    QString pathToTicketsBase;

public:   
    void clearTicketBase();

    TicketBase(QString pathToTicketBase=":/ticketBase/TestBase.json", QString pathToStatisticBase="./statisticBase.json");

    Ticket* getTicket(int index); //ебат

    QList<Ticket*> getRandomTicketList(TicketStatus status, int amountOfTickets=10);
    QList<Ticket*> getRandomTicketList(QList <TicketStatus> statuses, int amountOfTickets=10);

    void saveAnswerInStatistic(int ticketIndex, TicketAnswerType answer);
    void saveAnswerInStatistic(Ticket* ticket, TicketAnswerType answer);

    void updateStatisticInBase();

    int getChanceToPassExam();
    int getAllLearnedProc();
    int getTodayLearnedProc();

    int getAllTicketsCount();
    int getLearnedTicketsCount();
    int getHardTicketsCount();
    int getForgottenTicketsCount();


    //--убрать?
    void printTicketInfo(int ticketIndex)
    {
        statistic.printTicketInfo(ticketIndex);
    }

    ~TicketBase();

    friend class TicketsDataBaseReader;
};

#endif // TICKETBASE_H
