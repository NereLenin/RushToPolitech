#include "ticketbase.h"


TicketBase::TicketBase(QString pathToTicketBase, QString pathToStatisticBase)
{
    this->pathToTicketsBase = pathToTicketBase;
    this->pathToStatisticBase = pathToStatisticBase;

    baseVersion = 0.0;

    TicketsDataBaseReader::readTicketsFromJsonDB(pathToTicketsBase,*this);

    statistic.setPathToStatisticBase(this->pathToStatisticBase);
    statistic.setTicketBase(&ticketsBase);
    statistic.updateStatisticBase();
}

const Ticket *TicketBase::getTicket(int index)
{
    if(index >=0 && index < ticketsBase.size())
    {
        return ticketsBase[index];
    }

    qDebug() << "Try to get incorrect index from ticketBase getTicket(" << index << ")";
    return nullptr;
}

QList <Ticket*> TicketBase::getRandomTicketList(TicketStatus status, int amountOfTickets)
{
    QList <Ticket*> allTickets = statistic.getListOfTickets(status);
    QList <Ticket*> randomTicketsList;

    if(!allTickets.empty())
    {
        int ticketIndexMax = allTickets.size();
        int randIndexOfTicket = 0;
        for(int i =0; i < amountOfTickets; i++)
        {
            randIndexOfTicket = statistic.getRandomNumber(0,ticketIndexMax);
            randomTicketsList.append(allTickets[randIndexOfTicket]);
        }
    }

    return randomTicketsList;
}

QList<Ticket *> TicketBase::getRandomTicketList(QList<TicketStatus> statuses, int amountOfTickets)
{

        int amountOfRepeatStatuses = statuses.size();

        if(amountOfRepeatStatuses == 0)
            return getRandomTicketList(TicketStatus::Any, amountOfTickets);


        int sizeOfListOneStatus = amountOfTickets/amountOfRepeatStatuses;

        QList <Ticket*> ticketsList;

        for(int i=0;i<statuses.size();i++)
            ticketsList.append(getRandomTicketList(statuses[i],sizeOfListOneStatus));

        return ticketsList;
}

void TicketBase::saveAnswerInStatistic(int ticketIndex, TicketAnswerType answer)
{
    statistic.saveAnswerInStatistic(ticketIndex, answer);
}

void TicketBase::saveAnswerInStatistic(Ticket *ticket, TicketAnswerType answer)
{
    statistic.saveAnswerInStatistic(ticket->getIndex(), answer);
}

void TicketBase::updateStatisticInBase()
{
    statistic.updateStatisticBase();
}

int TicketBase::getChanceToPassExam()
{
    return statistic.getChanceToPassExam();
}

int TicketBase::getAllLearnedProc()
{
    return statistic.getAllLearnedProc();
}

int TicketBase::getTodayLearnedProc()
{
    return statistic.getTodayLearnedProc();
}

int TicketBase::getAllTicketsCount()
{
    return statistic.getListOfTickets(TicketStatus::Any).size();
}

int TicketBase::getLearnedTicketsCount()
{
    return statistic.getListOfTickets(TicketStatus::Learned).size();
}

int TicketBase::getHardTicketsCount()
{
    return statistic.getListOfTickets(TicketStatus::Hard).size();
}

int TicketBase::getForgottenTicketsCount()
{
    return statistic.getListOfTickets(TicketStatus::Forgotten).size();
}

void TicketBase::clearTicketBase()
{
    for(int i=0;i<ticketsBase.size();i++)
        delete ticketsBase[i];
}

TicketBase::~TicketBase()
{
   clearTicketBase();
}


