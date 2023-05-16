#include "learnsession.h"

void LearnSession::defaultLearnSession()
{
    pushListOfTickets(base->getRandomTicketList(TicketStatus::Unlearned,ticketsInOneSession));

    qDebug() << "LearnSession::defaultLearnSession";
}

void LearnSession::repeatHardSession()
{
    pushListOfTickets(base->getRandomTicketList(TicketStatus::Hard,ticketsInOneSession));

    qDebug() << "LearnSession::repeatHardSession";
}

void LearnSession::repeatWithTimerSession()
{
    timer.Stop();
    timer.setTime(timeToFinishSessionInMinutes);

    QList<Ticket*> listToPush = base->getRandomTicketList(TicketStatus::Learned,ticketsInOneSession);
    pushListOfTickets(listToPush);

    if(listToPush.size() > 0)//если нечего учить и таймер не нужен
        timer.Start();
}

void LearnSession::repeatRandomSession()
{
    QList <Ticket*> randomTickets = base->getRandomTicketList({TicketStatus::Hard, TicketStatus::Forgotten, TicketStatus::Learned},ticketsInOneSession);
    pushListOfTickets(randomTickets);
    qDebug() << "LearnSession::repeatRandomSession " << randomTickets.size();
}

void LearnSession::repeatForgottenSession()
{
    qDebug() << "LearnSession::repeatForgottenSession";
    pushListOfTickets(base->getRandomTicketList(TicketStatus::Forgotten,ticketsInOneSession));
}

void LearnSession::learnFailedTicketsSession()
{
    //для того чтобы указать что у нас больше не идет текущая сессия, а идет
    //отработка косячных билетов, меняем текущий режим
    if(currentRegime == Exam || currentRegime == DefaultLearning)
    {
        currentRegime = LearnFailedFromLearnOrExam;
    }else{
        currentRegime = LearnFailedFromRepeat;
    }


    qDebug() << "LearnSession::LearnFailed";
    pushListOfTickets(listOfWrongTickets);

    //обнуляем все, чтоб статистика по повтору была корректной
    countOfWrongAnswer = countOfRightAnswer = currentLearnedTicketNumber = 0;

    timer.Stop();

    listOfWrongTickets.clear();
    sessionLasting.Stop();//останавливаем подсчет времени на сессию
    sessionLasting.Start();//начинаем с начала
}

void LearnSession::ExamSession()
{
    qDebug() << "LearnSession::ExamSession";

    currentLearnedTicketNumber = 1;

    timer.Stop();
    timer.setTime(examTime);//устанавливаем сколько времени на сессию

    QList<Ticket*> listToPush = base->getRandomTicketList(TicketStatus::Any,ticketsInExamSession);

    this->pushListOfTickets(listToPush);

    if(listToPush.size() > 0)//если билетов нет не запускаем таймер, чтоб небыло таймаута
        timer.Start();

    sessionLasting.Stop();//останавливаем подсчет времени на сессию
    sessionLasting.Start();//начинаем с начала

    emit learnSessionStatisticChanged();
}
//----------end of sessions-----------------

void LearnSession::saveTicketInList(Ticket *ticket)
{
    bool thereAreDublicate = false;

    for(int i=0;i<listOfWrongTickets.size();i++)
    {
        //это можно получше сделать дядь ты чо гонеш
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
    currentLearnedTopic = nullptr;

    countOfRightAnswer = countOfWrongAnswer =
    currentLearnedTicketNumber = 0;

    currentRegime = TypeLearning::DefaultLearning;


    //запуск таймера отмеряющего время длительности сессии
    sessionLasting.setRegime(TimerType::Stopwatch);

    QObject::connect(&sessionLasting, &MyTimer::timeUpdated,
                     this, &LearnSession::onTimeChanged);

    sessionLasting.Start();

    //настройка таймера обратного отчета для режимов со временем

    QObject::connect(&timer, &MyTimer::timeOut,
                     this, &LearnSession::onTimerTimeOut);

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
    case LearnTicketsInTopic: learnTicketsInTopic(currentLearnedTopic); break;
    case Exam: ExamSession(); break;
    default:
        qDebug() << "Can't do this session from controller";
        break;
    }
}

void LearnSession::setCurrentLearnedTopic(Topic *newCurrentLearnedTopic)
{
    currentLearnedTopic = newCurrentLearnedTopic;
}

LearnSession::TypeLearning LearnSession::getCurrentRegime() const
{
    return LearnSession::currentRegime;
}

int LearnSession::getCountRight() const
{
    return countOfRightAnswer;
}

int LearnSession::getCountWrong() const
{
    return countOfWrongAnswer;
}

int LearnSession::getCurrentTicketNumber() const
{
    return this->currentLearnedTicketNumber;
}

int LearnSession::getCountOfTicketsInSession() const
{
    switch(currentRegime){
    case Exam: return ticketsInExamSession; break;
    default: return ticketsInOneSession; break;
    }
}

QList<Ticket *> LearnSession::getListOfWrongTicket()
{
    return listOfWrongTickets;
}

QTime LearnSession::getSessionLasting() const
{
    return sessionLasting.getCurrentTime();
}

QTime LearnSession::getTimerTime() const
{
    return timer.getCurrentTime();
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

    //Этот слот обрабатывается когда пользователь отвечает на вопрос
    //поэтому мы тут обновляем количество пройденных билетов
    if(currentLearnedTicketNumber < getCountOfTicketsInSession())
        currentLearnedTicketNumber++;

    emit learnSessionStatisticChanged();
}

void LearnSession::onStartLearningFailedTickets()
{
    this->learnFailedTicketsSession();
}

void LearnSession::onTimeChanged()
{
    emit learnSessionTimeChanged();
}

void LearnSession::onTimerTimeOut()
{
    qDebug() << "timeOut";

    onFinishSession();
    emit pushFinalScreen();
}

void LearnSession::onFinishSession()
{
    qDebug() << "onFinishSession";

    //стопим таймеры
    timer.Stop();
    sessionLasting.Stop();

    //сохраняем результаты сесси в базе статистики/в файле
    base->updateStatisticInBase();

    //обновляем инФу о таймерах после остановки
    emit learnSessionTimeChanged();
}
