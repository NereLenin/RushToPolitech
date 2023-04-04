#ifndef TICKETSSTATISTICSERVICE_H
#define TICKETSSTATISTICSERVICE_H
#include <QList>
#include <QRandomGenerator>
#include "ticketstatisticdatabasedriver.h"

class ITicketStatistic{
protected:
    ITicketStatistic(){}

public:
    virtual void saveAnswerInStatistic(int ticketIndex, TicketAnswerType answer) = 0;
    virtual void saveAnswerInStatistic(Ticket* ticket, TicketAnswerType answer) = 0;

    virtual int getChanceToPassExam() = 0;
    virtual int getAllLearnedProc() = 0;
    virtual int getTodayLearnedProc() = 0;
};


class TicketsStatisticService : public ITicketStatistic
{
private:
    QString pathToStatisticBase;
    QList<TicketInfo> ticketStatisticBase;

    QList <Ticket*> *ticketsBase;
    QRandomGenerator *randomGenerator;

    int dayBonusToChanceToPassExam;

    void setDayBonusToChanceToPassExam(int bonus);
    void setRandomDayBonusToChanceToPassExam();

    bool isTicketInStatisticBase(const Ticket* ticket);
    void createTicketInBase(const Ticket* ticket);

    void saveStatisticInBase();//обвязки для DBclass
    void loadStatisticBase();

    TicketInfo* getTicketInfo(const Ticket* ticket);

public:
    TicketsStatisticService();

    void setPathToStatisticBase(QString pathToStatisticBase);
    void setTicketBase(QList <Ticket*> *ticketsBase);

    void updateStatisticBase();


    QList<Ticket*> getListOfTickets(TicketStatus ticketStatus);

    void saveAnswerInStatistic(int ticketIndex, TicketAnswerType answer);
    void saveAnswerInStatistic(Ticket* ticket, TicketAnswerType answer);

    int getChanceToPassExam();
    int getAllLearnedProc();
    int getTodayLearnedProc();





    int getRandomNumber(int min, int max);

    ~TicketsStatisticService();

    //убрать
    void printTicketInfo(int ticketIndex); //надо?

    friend class TicketStatisticDataBaseDriver;
};

#endif // TICKETSSTATISTICSERVICE_H
