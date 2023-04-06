#include "appengine.h"

void AppEngine::bindQMLSlotSignalConnections(QObject *rootObject)
{
    if(rootObject==nullptr)
    {
        qDebug() << "try slot/signal connection with null rootObject";
        return;
    }

    //соединяем сигнал выбора ответа на форме с слотом зеркалом в движке
    QObject::connect(rootObject,SIGNAL(saveAnswerInStatistic(int,bool)),
                     this,SLOT(onSaveAnswerInStatistic(int,bool)));

    //соединяем сигналы QML о начале учебной сессии
    //с слотом-контроллером этого режима

    QObject::connect(rootObject,SIGNAL(startLearningSession()),
                     this,SLOT(learnController()));

    QObject::connect(rootObject,SIGNAL(startRepeatHardSession()),
                     this,SLOT(repeatHardController()));

    QObject::connect(rootObject,SIGNAL(startRepeatWithTimerSession()),
                     this,SLOT(repeatWithTimerController()));

    QObject::connect(rootObject,SIGNAL(startRepeatRandomSession()),
                     this,SLOT(repeatRandomController()));

    QObject::connect(rootObject,SIGNAL(startRepeatForgottenSession()),
                     this,SLOT(repeatForgottenController()));

    QObject::connect(rootObject,SIGNAL(startExamSession()),
                     this,SLOT(ExamController()));

}

void AppEngine::connectCurrentSessionWithEngine()
{
    if(currentSession == nullptr)
     {
        qDebug() << "try connect null session";
        return;
     }
    //
    QObject::connect(this,          SIGNAL(saveStatisticInLearningSession(int,TicketAnswerType)),
                     currentSession,SLOT(onSaveStatisticInLearningSession(int,TicketAnswerType)));

    QObject::connect(currentSession,SIGNAL(pushListOfTickets(QList <Ticket*>, QString)),
                     this,          SLOT(onLearnSessionFillStack(QList <Ticket*>,QString)));

}

void AppEngine::disconnectCurrentSessionWithEngine()
{
    if(currentSession == nullptr)
     {
        qDebug() << "try disconnect null session";
        return;
     }

    currentSession->disconnect(this);
}

void AppEngine::startLearningSession(TypeLearning regime)
{
    if(currentSession != nullptr)
        onEndLearningSessions();

    currentSession = LearnSession::createSession(&base,regime);
    connectCurrentSessionWithEngine();
    currentSession->StartSession();//фу блять с большой буквы почему
}



AppEngine::AppEngine(QObject *parent, QQmlApplicationEngine *engine)
    : QObject{parent}
{
    currentSession = nullptr;

    this->engine = engine;

    teacher.setTicketBase(&base);

    this->engine->rootContext()->setContextProperty("appEngine",this);

    bindQMLSlotSignalConnections(this->engine->rootObjects()[0]);
}

void AppEngine::emitPushSignalForTicket(Ticket *ticket)
{

    switch(ticket->getType())
    {
        case TicketType::selectableAnswerTicket:
        {
            SelectableAnswerTicket *currentTicket = dynamic_cast<SelectableAnswerTicket*>(ticket);
            emit pushSelectable(currentTicket->getIndex(), currentTicket->getQuestionText(),currentTicket->getImageUrl(),
                                  currentTicket->getAnswer(0),currentTicket->getAnswerImageUrl(0),
                                  currentTicket->getAnswer(1),currentTicket->getAnswerImageUrl(1),
                                  currentTicket->getAnswer(2),currentTicket->getAnswerImageUrl(2),
                                  currentTicket->getAnswer(3),currentTicket->getAnswerImageUrl(3),
                                  currentTicket->getIndexOfCorrectAnswer());
        }
        break;
    case TicketType::inputAnswerTicket:
    {
        InputAnswerTicket *currentTicket = dynamic_cast<InputAnswerTicket*>(ticket);
        emit pushInputable(currentTicket->getIndex(),currentTicket->getCorrectAnswer(),currentTicket->getQuestionText(), currentTicket->getImageUrl());
    }
    break;

    }

}

void AppEngine::learnController()
{
    qDebug() << "AppEngine::learnController";

    startLearningSession(TypeLearning::DefaultLearning);
}

void AppEngine::repeatHardController()
{
    startLearningSession(TypeLearning::RepeatHard);
}

void AppEngine::repeatWithTimerController()
{
    startLearningSession(TypeLearning::RepeatWithTimer);
}

void AppEngine::repeatRandomController()
{
   startLearningSession(TypeLearning::RepeatRandom);
}

void AppEngine::repeatForgottenController()
{
    startLearningSession(TypeLearning::RepeatForgotten);
}

void AppEngine::ExamController()
{
    startLearningSession(TypeLearning::Exam);
}

void AppEngine::onSaveAnswerInStatistic(int index, bool isCorrect)
{


    emit saveStatisticInLearningSession(index, (TicketAnswerType)isCorrect);
}

void AppEngine::onLearnSessionFillStack(QList<Ticket *> ticketsToPush, QString finalScreen)
{
        if(ticketsToPush.size() == 0)
        {
           qDebug() << "Пушим нулевой билет";
           emit pushSelectable(0,"Нет больше билетов брат...\nПрости брат....\n","qrc:/icons/logo.png","Спасибо......\n я понял брат.....","","Ты чо попутал я за\n тебя 0 руб заплатил....","","","","","",1);
           return;
        }

        emit pushStack(finalScreen);

        for(int i=0;i<ticketsToPush.size();i++)
        {
            emitPushSignalForTicket(ticketsToPush[i]);
        }

}

void AppEngine::onEndLearningSessions()
{
    if(currentSession == nullptr)
    {
        qDebug() << "try end session then it's null";
        return;
    }

    disconnectCurrentSessionWithEngine();
    delete currentSession;
}
