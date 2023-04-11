#include "appengine.h"

void AppEngine::bindQMLSlotSignalConnections()
{
    if(engine==nullptr)
    {
        qDebug() << "don't have any engine";
        return;
    }

    QObject *rootObject = engine->rootObjects()[0];

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

    //прогон неправильно отвеченных в ходе сессии билетов
    QObject::connect(rootObject,SIGNAL(startLearnFailedTicketsSession()),
                     this,SLOT(onStartLearnFailedTicketsSession()));

    //прошел все тикеты и дошел до последнего экрана
    QObject::connect(rootObject,SIGNAL(finishLearningSession()),
                     this,SLOT(onFinishLearningSession()));
    //убежал из сессии
    QObject::connect(rootObject,SIGNAL(endLearningSessions()),
                     this,SLOT(onEndLearningSessions()));

}

void AppEngine::connectCurrentSessionWithEngine()
{
    if(currentSession == nullptr)
     {
        qDebug() << "try connect null session";
        return;
     }

    //от движка к сессии
    QObject::connect(this,          SIGNAL(startLearningFailedTickets()),
                     currentSession,SLOT(onStartLearningFailedTickets()) );

    QObject::connect(this,          SIGNAL(saveStatisticInLearningSession(int,TicketAnswerType)),
                     currentSession,SLOT(onSaveStatisticInLearningSession(int,TicketAnswerType)) );

    QObject::connect(this,          SIGNAL(finishSession()),
                     currentSession,SLOT(onFinishSession()) );

    //сигналы от сессии к нашему движку
    QObject::connect(currentSession,SIGNAL(pushListOfTickets(QList <Ticket*>)),
                     this,          SLOT(onLearnSessionFillStack(QList <Ticket*>)));

    QObject::connect(currentSession,SIGNAL(learnSessionStatisticChanged()),
                     this,          SLOT(onLearnSessionStatisticChanged()));

    QObject::connect(currentSession,SIGNAL(learnSessionStatisticChanged()),
                     this,          SLOT(onLearnSessionStatisticChanged()));

    QObject::connect(currentSession,SIGNAL(learnSessionTimeChanged()),
                     this,          SLOT(onLearnSessionTimeChanged()));

    QObject::connect(currentSession,SIGNAL(pushFinalScreen()),
                     this,          SLOT(onLearnSessionPushFinalPage()));

    //QObject::connect(currentSession,SIGNAL(learnSessionTimeOut()),
    //                 this,          SLOT(onLearnSessionTimerTimeOut()));


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

QMap<TypeLearning, QString> AppEngine::fillFinishScreens()
{
    QMap<TypeLearning, QString> finishScreens;
    finishScreens[TypeLearning::DefaultLearning] = "qrc:/qml/FinishLearnScreen.qml";
    finishScreens[TypeLearning::RepeatHard] = "qrc:/qml/FinishLearnScreen.qml";
    finishScreens[TypeLearning::RepeatWithTimer] = "qrc:/qml/FinishLearnScreen.qml";
    finishScreens[TypeLearning::RepeatRandom] = "qrc:/qml/FinishLearnScreen.qml";
    finishScreens[TypeLearning::RepeatForgotten] = "qrc:/qml/FinishLearnScreen.qml";
    finishScreens[TypeLearning::Exam] = "qrc:/qml/FinishExamFailed.qml";
    return finishScreens;
}



AppEngine::AppEngine(QQmlApplicationEngine *engine, QObject *parent)
    : QObject{parent}
{
    currentSession = nullptr;

    this->engine = engine;

    this->engine->rootContext()->setContextProperty("appEngine",this);
    this->engine->rootContext()->setContextProperty("listWrongTickets",wrongTicketsModel);

    QObject::connect(this->engine,&QQmlApplicationEngine::objectCreated,
                     this        ,&AppEngine::onQmlEngineObjectCreated);


    finishScreens = fillFinishScreens();
}

int AppEngine::getChanceToPassExam()
{
    return base.getChanceToPassExam();
}

int AppEngine::getProcOfAllLearned()
{
    return base.getAllLearnedProc();
}

int AppEngine::getProcOfTodayLearned()
{
    return base.getTodayLearnedProc();
}

int AppEngine::getAllTicketsCount()
{
    return base.getAllTicketsCount();
}

int AppEngine::getLearnedTicketsCount()
{
    return base.getLearnedTicketsCount();
}

int AppEngine::getHardTicketsCount()
{
    return base.getHardTicketsCount();
}

int AppEngine::getForgottenTicketsCount()
{
    return base.getForgottenTicketsCount();
}

QString AppEngine::getTitle()
{
    return "Yulya is pure sex";
}

void AppEngine::fillTicketModelFromSession()
{

    wrongTicketsModel.clear();
    QList <QObject*> modelList;
    if(currentSession != nullptr)
    {
        for(int i=0;i<currentSession->getListOfWrongTicket().size();i++)
            modelList.append((currentSession->getListOfWrongTicket())[i]);
    }
    wrongTicketsModel.setValue(modelList);
}

int AppEngine::getCountOfRightAnswer()
{
    if(currentSession == nullptr) return 0;
    return currentSession->getCountRight();
}

int AppEngine::getCountOfWrongAnswer()
{
    if(currentSession == nullptr) return 0;
    return currentSession->getCountWrong();
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
    qDebug() << "AppEngine::onSaveAnswerInStatistic";
    emit saveStatisticInLearningSession(index, (TicketAnswerType)isCorrect);
}

void AppEngine::onStartLearnFailedTicketsSession()
{
    emit startLearningFailedTickets();
}

void AppEngine::onLearnSessionFillStack(QList<Ticket *> ticketsToPush)
{

        if(ticketsToPush.size() == 0)
        {
           qDebug() << "Пушим нулевой билет";
           emit pushSelectable(0,textOfNullTicket,"qrc:/icons/logo.png","Спасибо......\n я понял брат.....","","Всм нет я за\n тебя 0 руб заплатил....\nДАЙ","","","","","",1);
           emit finishSession();
           return;
        }

        emit clearStack();

        onLearnSessionPushFinalPage();

        for(int i=0;i<ticketsToPush.size();i++)
        {
            emitPushSignalForTicket(ticketsToPush[i]);
        }

}

void AppEngine::onLearnSessionPushFinalPage()
{
    if(currentSession!=nullptr)
        emit pushStack(finishScreens[currentSession->getCurrentRegime()]);
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
    currentSession = nullptr;
}

void AppEngine::onFinishLearningSession()
{
    emit finishSession();
}

void AppEngine::onLearnSessionStatisticChanged()
{
    emit sessionStatisticChanged();

    fillTicketModelFromSession();
    this->engine->rootContext()->setContextProperty("listWrongTickets",this->wrongTicketsModel);
}

void AppEngine::onLearnSessionTimeChanged()
{
    emit sessionTimeChanging();
}

//void AppEngine::onLearnSessionTimerTimeOut()
//{
//    //вот эту штуку перенести в LS
//    //emit clearStack();
//    //emit pushStack("qrc:/qml/FinishLearnScreen.qml");
//    //qDebug() << "Time is out bro";
//}

void AppEngine::onQmlEngineObjectCreated()
{
    this->bindQMLSlotSignalConnections();
}
