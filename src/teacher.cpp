#include "teacher.h"
#include <string>

void Teacher::setTimeOut()
{

    this->isTimeOut = true;
    qDebug() << "\ntimerChanged!!!!\n" << isTimeOut;
    timer.stop();
}

Teacher::Teacher(QObject *parent)
    : QObject{parent}
{
    ticketBase = NULL;
    int timerMinutesToLearn = 5;

    int oneMinInMs = 60000;
    timer.setInterval(timerMinutesToLearn * oneMinInMs);
    isTimeOut = false;

    connect(&timer,SIGNAL(timeout()), SLOT(setTimeOut()));
}

void Teacher::setTicketBase(TicketBase *ticketBase)
{
    if(ticketBase == NULL)
    {
        //исключение
        return;
    }
    this->ticketBase = ticketBase;
}

void Teacher::workOnTicket(Ticket *workedTicket)
{
    workedTicket->debugPrint();

    TicketAnswerType correctnessOfAnswer;

    std::string strOfAnswer;
    std::cout << "enter correct answer:";
    std::cin >> strOfAnswer;

    correctnessOfAnswer =  workedTicket->isCorrectAnswer(QString::fromStdString(strOfAnswer));

    ticketBase->saveAnswerInStatistic(workedTicket,correctnessOfAnswer);

    if(correctnessOfAnswer == TicketAnswerType::Correct) qDebug() << "Correct!";
    else qDebug() << "Wrong!";
}

void Teacher::workOnTicketList(QList<Ticket*> listOfTickets, bool withTimer)
{
    if(listOfTickets.isEmpty())
    {
        qDebug() << "what do you want to work for? It's empty list";
        return;
    }

    if(withTimer)
    {
        isTimeOut = false;
        timer.start();

        for(int i=0;i<listOfTickets.size() && !isTimeOut; i++)
        {
            qDebug() << "isTimeOut:" << isTimeOut;
            workOnTicket(listOfTickets[i]);
        }
    }
    else
    {
        for(int i=0;i<listOfTickets.size();i++){
            workOnTicket(listOfTickets[i]);}
    }

    ticketBase->updateStatisticInBase();
}


void Teacher::learnTickets(int amountOfTickets)
{
    workOnTicketList(ticketBase->getRandomTicketList(TicketStatus::Unlearned, amountOfTickets));
}

void Teacher::repeatTickets(RepeatingTypes type, int amountOfTickets)
{
    switch(type)
    {
    case RepeatingTypes::onlyHardTickets :
        repeatOnlyHardTickets(amountOfTickets);
        break;
    case RepeatingTypes::onlyForgotten :
        repeatOnlyForgotten(amountOfTickets);
        break;
    case RepeatingTypes::withTimer:
        repeatOnlyHardTickets(amountOfTickets);
        break;
    case RepeatingTypes::randomTickets:
        repeatRandomTickets(amountOfTickets);
        break;
    default:
        qDebug() << "unknowing type of repeat";
        return;
        break;
    };
}

void Teacher::repeatOnlyHardTickets(int amountOfTickets)
{
    workOnTicketList(ticketBase->getRandomTicketList(TicketStatus::Hard, amountOfTickets));
}

void Teacher::repeatOnlyForgotten(int amountOfTickets)
{
    workOnTicketList(ticketBase->getRandomTicketList(TicketStatus::Forgotten, amountOfTickets));
}

void Teacher::repeatWithTimer(int amountOfTickets)
{

    workOnTicketList(ticketBase->getRandomTicketList(TicketStatus::Learned, amountOfTickets), true);
    if(isTimeOut)
    {
        qDebug() << "Time is gone";
    }
}

void Teacher::repeatRandomTickets(int amountOfTickets)
{
    workOnTicketList(ticketBase->getRandomTicketList({TicketStatus::Learned ,TicketStatus::Hard, TicketStatus::Forgotten},amountOfTickets));
}
