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

Ticket *TicketBase::getTicket(int index)
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

        QList <Ticket*> ticketsList;

        if(amountOfRepeatStatuses == 0)
            return ticketsList;

        QList <Ticket*> listOfCurrentStatus;

        bool baseHasTicketsWithThisStatus = false;
        for(int i = 0; i < statuses.size();i++)
        {
            listOfCurrentStatus = getRandomTicketList(statuses[i],1);
            if(listOfCurrentStatus.size() > 0)
            {
                baseHasTicketsWithThisStatus = true;
                break;
            }
        }

        listOfCurrentStatus.clear();

        int neededTicketOneStatus  = amountOfTickets/amountOfRepeatStatuses;
        while(ticketsList.size() < amountOfTickets && baseHasTicketsWithThisStatus && neededTicketOneStatus > 0)
        {
            neededTicketOneStatus = (double)(amountOfTickets - ticketsList.size())/(double)amountOfRepeatStatuses;
            for(int i = 0; i < statuses.size() && ticketsList.size() < amountOfTickets;i++)
            {
                listOfCurrentStatus = getRandomTicketList(statuses[i],neededTicketOneStatus);
                ticketsList.append(listOfCurrentStatus);
            }
        }

        qDebug() << "In mixed ticketsList amount of tickets:" << ticketsList.size();
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
    return ticketsBase.size();
}

int TicketBase::getLearnedTicketsCount()
{
    if(ticketsBase.size() == 0)
        return 0;

    return statistic.getListOfTickets(TicketStatus::Learned).size();
}

int TicketBase::getHardTicketsCount()
{
    if(ticketsBase.size() == 0)
        return 0;

    return statistic.getListOfTickets(TicketStatus::Hard).size();
}

int TicketBase::getForgottenTicketsCount()
{
    if(ticketsBase.size() == 0)
        return 0;

    return statistic.getListOfTickets(TicketStatus::Forgotten).size();
}

void TicketBase::clearTicketBase()
{
    for(int i=0;i<ticketsBase.size();i++)
    {
        delete ticketsBase[i];
        ticketsBase[i] = nullptr;
    }
    ticketsBase.clear();
    statistic.updateStatisticBase();
}

TicketBase::~TicketBase()
{
   clearTicketBase();
}


