#include "learnsession.h"

void LearnSession::defaultLearnSession()
{
    this->pushListOfTickets(base->getRandomTicketList(TicketStatus::Unlearned,ticketsInOneSession),"qrc:/qml/FinishLearnScreen.qml");

    qDebug() << "LearnSession::defaultLearnSession";

}

void LearnSession::repeatHardSession()
{
    this->pushListOfTickets(base->getRandomTicketList(TicketStatus::Hard,ticketsInOneSession),"qrc:/qml/FinishLearnScreen.qml");

    qDebug() << "LearnSession::repeatHardSession";
}

void LearnSession::repeatWithTimerSession()
{
    qDebug() << "LearnSession::repeatWithTimerSession Этот режим пока не готов так что лови ";
    defaultLearnSession();
}

void LearnSession::repeatRandomSession()
{
    this->pushListOfTickets(base->getRandomTicketList({TicketStatus::Hard, TicketStatus::Forgotten, TicketStatus::Learned, TicketStatus::Unlearned},ticketsInOneSession),"qrc:/qml/FinishLearnScreen.qml");
    qDebug() << "LearnSession::repeatRandomSession";
}

void LearnSession::repeatForgottenSession()
{
    qDebug() << "LearnSession::repeatForgottenSession";
    this->pushListOfTickets(base->getRandomTicketList(TicketStatus::Forgotten,ticketsInOneSession),"qrc:/qml/FinishLearnScreen.qml");
}

void LearnSession::learnFailedTicketsSession()
{
    qDebug() << "LearnSession::LearnFailed";
    pushListOfTickets(listOfWrongTickets,"qrc:/qml/FinishLearnScreen.qml");

    //обнуляем все, чтоб статистика по повтору была корректной
    countOfWrongAnswer = countOfRightAnswer = 0;
    listOfWrongTickets.clear();
    sessionLasting.Stop();//останавливаем подсчет времени на сессию
    sessionLasting.Start();//начинаем с начала
}

void LearnSession::ExamSession()
{
    qDebug() << "LearnSession::ExamSession не готово";
    defaultLearnSession();
}

void LearnSession::saveTicketInList(Ticket *ticket)
{
    bool thereAreDublicate = false;

    for(int i=0;i<listOfWrongTickets.size();i++)
    {
        if(listOfWrongTickets[i]->getIndex() == ticket->getIndex())
        {
            thereAreDublicate = true;
            break;
        }
    }

    if(!thereAreDublicate)
        listOfWrongTickets.append(ticket);

}

LearnSession::LearnSession(QObject *parent)
    : QObject{parent}
{
    base = nullptr;
    countOfRightAnswer = countOfWrongAnswer = 0;

    currentRegime = TypeLearning::DefaultLearning;


    //запуск таймера отмеряющего время сессии
    sessionLasting.setRegime(TimerType::Stopwatch);

    QObject::connect(&sessionLasting, &MyTimer::timeUpdated,
                     this, &LearnSession::onLastingTimerChanged);

    sessionLasting.Start();
}

LearnSession *LearnSession::createSession(TicketBase *ticketBase, TypeLearning regime)
{
    LearnSession *newSession = new LearnSession();
    newSession->base = ticketBase;
    newSession->currentRegime = regime;

    return newSession;
}

void LearnSession::StartSession()
{
    switch(currentRegime){
    case DefaultLearning: defaultLearnSession(); break;
    case RepeatHard: repeatHardSession(); break;
    case RepeatWithTimer: repeatWithTimerSession(); break;
    case RepeatRandom: repeatRandomSession(); break;
    case RepeatForgotten: repeatForgottenSession(); break;
    case Exam: ExamSession(); break;
    }
}

int LearnSession::getCountRight() const
{
    return countOfRightAnswer;
}

int LearnSession::getCountWrong() const
{
    return countOfWrongAnswer;
}

QList<Ticket *> LearnSession::getListOfWrongTicket()
{
    return listOfWrongTickets;
}

QTime LearnSession::getSessionLasting() const
{
    return sessionLasting.getCurrentTime();
}

void LearnSession::onSaveStatisticInLearningSession(int index, TicketAnswerType correcness)
{  
    if(correcness == TicketAnswerType::Wrong)
    {
        saveTicketInList(base->getTicket(index));
        countOfWrongAnswer++;
    }
    else
    {
        countOfRightAnswer++;
    }

    base->saveAnswerInStatistic(index,correcness);
    base->updateStatisticInBase();//вот эту хуйню мож в конец сессии сунуть?

    emit learnSessionStatisticChanged();
}

void LearnSession::onStartLearningFailedTickets()
{
    this->learnFailedTicketsSession();
}

void LearnSession::onLastingTimerChanged()
{
    emit learnSessionLastingTimeChanged();
}
