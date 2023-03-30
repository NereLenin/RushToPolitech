#ifndef TICKETBASE_H
#define TICKETBASE_H
#include <ticketsdatabasereader.h>
#include <ticketsstatisticservice.h>


class TicketBase : public ITicketStatistic
{
private:
    QList <Ticket*> ticketsBase;
    double baseVersion;

    TicketsStatisticService statistic;

    QString pathToStatisticBase;
    QString pathToTicketsBase;

    void clearTicketBase();
public:
    TicketBase();

    QList<Ticket*> getRandomTicketList(TicketStatus status, int amountOfTickets=10);
    QList<Ticket*> getRandomTicketList(QList <TicketStatus> statuses, int amountOfTickets=10);

    void saveAnswerInStatistic(int ticketIndex, TicketAnswerType answer);
    void saveAnswerInStatistic(Ticket* ticket, TicketAnswerType answer);

    void updateStatisticInBase();

    int getChanceToPassExam();
    int getAllLearnedProc();
    int getTodayLearnedProc();

    //--убрать?
    void printTicketInfo(int ticketIndex)
    {
        statistic.printTicketInfo(ticketIndex);
    }

    ~TicketBase();

    friend class TicketsDataBaseReader;
};

#endif // TICKETBASE_H
