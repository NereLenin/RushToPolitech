#include "ticketsstatisticservice.h"


TicketsStatisticService::TicketsStatisticService()
{

    randomGenerator = QRandomGenerator::global();
    dayBonusToChanceToPassExam = 0;
}

int TicketsStatisticService::getRandomNumber(int min, int max)
{
    return randomGenerator->bounded(min,max);
}

void TicketsStatisticService::setPathToStatisticBase(QString pathToStatisticBase)
{
    this->pathToStatisticBase = pathToStatisticBase;
}

void TicketsStatisticService::setTicketBase(QList<Ticket *> *ticketsBase)
{
    this->ticketsBase = ticketsBase;
}

void TicketsStatisticService::updateStatisticBase()
{
    //если база пустая загружаемся из файла
    if(ticketStatisticBase.empty())
        loadStatisticBase();

    //если в базе статистики нет какого то нашего билета,создаем
    if(this->ticketsBase != NULL)
        for(int i=0; i< (*ticketsBase).size();i++)
            if(!isTicketInStatisticBase((*ticketsBase)[i]))
                createTicketInBase((*ticketsBase)[i]);

    //обновляем статусы билетов, чтобы некоторые стали "забытыми"
    for(int i=0;i<ticketStatisticBase.size();i++)
        ticketStatisticBase[i].updateStatus();

    //сохраняем все это в файл
    saveStatisticInBase();
}

TicketInfo *TicketsStatisticService::getTicketInfo(const Ticket *ticket)
{
    if(ticketStatisticBase.empty())
    {
        qDebug() << "emptyStatisticBase";
        //или update или искл
        return NULL;
    }
    if(ticket == NULL)
    {
        qDebug() << "getTicketInfo: empty inputTicket";
        return NULL;
    }

    for(int i=0;i <ticketStatisticBase.size();i++)
        if(ticket->getIndex() == ticketStatisticBase[i].getTicketIndex())
            return &ticketStatisticBase[i];

    return NULL;

}

void TicketsStatisticService::setDayBonusToChanceToPassExam(int bonus)
{
    if(bonus == 0)  setRandomDayBonusToChanceToPassExam();
    else this->dayBonusToChanceToPassExam = bonus;
}

void TicketsStatisticService::setRandomDayBonusToChanceToPassExam()
{
    this->dayBonusToChanceToPassExam = getRandomNumber(1,10);
}

void TicketsStatisticService::loadStatisticBase()
{
    TicketStatisticDataBaseDriver::loadStatisticBase(pathToStatisticBase,*this);
}

void TicketsStatisticService::printTicketInfo(int ticketIndex)
{
    if(!isTicketInStatisticBase((*ticketsBase)[ticketIndex]))
        createTicketInBase((*ticketsBase)[ticketIndex]);

    getTicketInfo((*ticketsBase)[ticketIndex])->debugPrint();
}

bool TicketsStatisticService::isTicketInStatisticBase(const Ticket *ticket)
{
    return getTicketInfo(ticket) != NULL;
}

void TicketsStatisticService::createTicketInBase(const Ticket *ticket)
{
    if(!isTicketInStatisticBase(ticket))
    {
        TicketInfo newTicket(ticket->getIndex());
        //newTicket.ticketIndex = ticket->index;
        ticketStatisticBase.append(newTicket);
    }
}

void TicketsStatisticService::saveStatisticInBase()
{
    TicketStatisticDataBaseDriver::saveStatisticInBase(*this,pathToStatisticBase);
}

QList<Ticket *> TicketsStatisticService::getListOfTickets(TicketStatus ticketStatus)//, int amountOfTickets)
{
    if(ticketsBase == NULL)
    {
        qDebug() << "emptyTicketBase";
        return *(new QList<Ticket*>());
        //исключение пустая база
    }

    QList<Ticket*> ticketsWithStatus;

    if(ticketStatus == TicketStatus::Any)
    {
        ticketsWithStatus = *ticketsBase;
    }
    else
    {
        for(int i=0;i < ticketsBase->size();i++)
        {
            if(!isTicketInStatisticBase((*ticketsBase)[i]))
                createTicketInBase((*ticketsBase)[i]);

            if(getTicketInfo((*ticketsBase)[i])->getTicketStatus() == ticketStatus)
                ticketsWithStatus.append((*ticketsBase)[i]);
        }
    }
    return ticketsWithStatus;
}

void TicketsStatisticService::saveAnswerInStatistic(int ticketIndex, TicketAnswerType answer)
{
    for(int i = 0; i < (*ticketsBase).size();i++)
        if((*ticketsBase)[i]->getIndex() == ticketIndex)
            getTicketInfo((*ticketsBase)[i])->saveAnswer(answer);

}

void TicketsStatisticService::saveAnswerInStatistic(Ticket *ticket, TicketAnswerType answer)
{
    if(ticket!=NULL)
        if(getTicketInfo(ticket) != NULL)
            getTicketInfo(ticket)->saveAnswer(answer);
}

int TicketsStatisticService::getChanceToPassExam()
{
    // проц количество выученных билетов - количество забытых в процентах от всех билетов - количество тяжелых в процентах от всех билетов и
    //+ от0-10ти проц - вот это дневной бонус хранящийся в статик бэйзе и обновляющийся каждый день

    //это вероятность шо ты приглянешся преоподу и он такой - вот те поступление за половое преступление
    //со мной или если вдруг еще шото такое произойдет

    double amountOfAllTickets = ticketsBase->size();

    double procLearned = getAllLearnedProc();
    double oneTicketInProc = 100.0/amountOfAllTickets;

    double amountOfForgotten = getListOfTickets(TicketStatus::Forgotten).size();
    double procForgotten = amountOfForgotten * oneTicketInProc;

    double amountOfHard = getListOfTickets(TicketStatus::Hard).size();
    double procHard = amountOfHard * oneTicketInProc;

    double chanceToPassExam = (procLearned - procForgotten - procHard) + dayBonusToChanceToPassExam;

    //qDebug() << chanceToPassExam << "=" << procLearned << "-" << procForgotten << "-" << procHard << "+" << dayBonusToChanceToPassExam;

    if(chanceToPassExam < 0) chanceToPassExam=0;
    if(chanceToPassExam > 100) chanceToPassExam=100;

    return chanceToPassExam;
}

int TicketsStatisticService::getAllLearnedProc()
{
    double amountOfAllTickets = ticketsBase->size();

    double amountOfLearnedTickets = getListOfTickets(TicketStatus::Learned).size();
    return (amountOfLearnedTickets/amountOfAllTickets) * 100.0;
}

int TicketsStatisticService::getTodayLearnedProc()
{
    QList<Ticket*> learnedList = getListOfTickets(TicketStatus::Learned);

    QDate today = QDate::currentDate();

    double amountOfTodayLearnedTickets=0;

    for(int i=0;i < learnedList.size();i++)
        if(getTicketInfo(learnedList[i])->getDateOfStatusChanged() == today)
            amountOfTodayLearnedTickets++;

    double amountOfAllTickets = ticketsBase->size();

    double procOfTodayLearned = (amountOfTodayLearnedTickets/amountOfAllTickets) * 100.0;

    return procOfTodayLearned;
}

TicketsStatisticService::~TicketsStatisticService()
{
    delete randomGenerator;
}

