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

void LearnSession::ExamSession()
{
    qDebug() << "LearnSession::ExamSession не готово";
    defaultLearnSession();
}

LearnSession::LearnSession(QObject *parent)
    : QObject{parent}
{
    base = nullptr;
    countOfRightAnswer = countOfWrongAnswer = 0;

    currentRegime = TypeLearning::DefaultLearning;
    //запуск таймера

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

void LearnSession::onSaveStatisticInLearningSession(int index, TicketAnswerType correcness)
{
    qDebug() << "saveStatistic in LearningSession SLOT: " << index << "correctenss: " << correcness;

    if(correcness == TicketAnswerType::Wrong)
    {
        listOfWrongTickets.append(base->getTicket(index));
        countOfWrongAnswer++;
    }
    else
    {
        countOfRightAnswer++;
    }

    emit learnSessionStatisticChanged();

    qDebug() << "count w:" << countOfWrongAnswer << " count right:" << countOfRightAnswer;
    base->saveAnswerInStatistic(index,correcness);
    base->updateStatisticInBase();//вот эту хуйню мож в конец сессии сунуть?


}
