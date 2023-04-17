#include "appengine.h"

#include <QEventLoop>

void delay(int millisecondsWait)
{
    QEventLoop loop;
    QTimer t;
    t.connect(&t, &QTimer::timeout, &loop, &QEventLoop::quit);
    t.start(millisecondsWait);
    loop.exec();
}

void AppEngine::bindQMLSlotSignalConnections()
{
    if(qmlEngine==nullptr)
    {
        qDebug() << "don't have any engine";
        return;
    }

    if(qmlEngine->rootObjects().empty())
    {
        qDebug() << "don't have any main page in engine";
        return;
    }

    if(qmlEngine->rootObjects()[0]->objectName() != "appMainScreen")
    {
        qDebug() << "Can't bind with main screen, it's not app Main Screen";
        return;
    }

    QObject *rootObject = qmlEngine->rootObjects()[0];

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

    currentSession = LearnSession::createSession(&tickets,regime);
    connectCurrentSessionWithEngine();
    currentSession->StartSession();//фу блять с большой буквы почему
}

QMap<TypeLearning, QString> AppEngine::fillFinishScreens()
{
    QMap<TypeLearning, QString> finishScreens;
    finishScreens[TypeLearning::DefaultLearning] =
    finishScreens[TypeLearning::RepeatHard] =
    finishScreens[TypeLearning::RepeatWithTimer] =
    finishScreens[TypeLearning::RepeatRandom] =
    finishScreens[TypeLearning::RepeatForgotten] =
    finishScreens[TypeLearning::LearnFailedFromRepeat] =
    finishScreens[TypeLearning::LearnFailedFromLearnOrExam]= "FinishLearnScreen.qml";

    finishScreens[TypeLearning::Exam] = "FinishExamScreen.qml";
    return finishScreens;
}



const QString AppEngine::getTextOfNullTicket() const {
    return textOfNullTicket;
}

void AppEngine::initialize()
{
    qmlEngine = nullptr;
    currentSession = nullptr;

    finishScreens = fillFinishScreens();
}

void AppEngine::connectToEngine(QQmlApplicationEngine *newEngine)
{
    if(newEngine!=nullptr && this->qmlEngine == nullptr){
        this->qmlEngine = newEngine;

        this->qmlEngine->rootContext()->setContextProperty("appEngine",this);
        this->qmlEngine->rootContext()->setContextProperty("listWrongTickets",wrongTicketsModel);

        QObject::connect(this->qmlEngine, &QQmlApplicationEngine::objectCreated,
                           this, &AppEngine::onQmlEngineObjectCreated);
     }
}


AppEngine::AppEngine(QObject* parent, QQmlApplicationEngine *qmlEngine)
    : QObject{parent}
{
    initialize();
    connectToEngine(qmlEngine);
}


int AppEngine::getChanceToPassExam()
{
    return tickets.getChanceToPassExam();
}

int AppEngine::getProcOfAllLearned()
{
    return tickets.getAllLearnedProc();
}

int AppEngine::getProcOfTodayLearned()
{
    return tickets.getTodayLearnedProc();
}

int AppEngine::getAllTicketsCount()
{
    return tickets.getAllTicketsCount();
}

int AppEngine::getLearnedTicketsCount()
{
    return tickets.getLearnedTicketsCount();
}

int AppEngine::getHardTicketsCount()
{
    return tickets.getHardTicketsCount();
}

int AppEngine::getForgottenTicketsCount()
{
    return tickets.getForgottenTicketsCount();
}

int AppEngine::getCurrentTicketNumber(){
    if(currentSession!=nullptr)
    {
        return currentSession->getCurrentTicketNumber();
    }
    return 0;
}

int AppEngine::getCountOfTicketsInSession(){
    if(currentSession!=nullptr)
    {
        return currentSession->getCountOfTicketsInSession();
    }
    return 0;
}

const QString AppEngine::getTitle() const
{
    return "Yulya is pure sex";
}

QString AppEngine::getTypeOfCurrentSession(){
    if(currentSession!=nullptr)
    {
        switch(currentSession->getCurrentRegime())
        {
        case TypeLearning::Exam: return "Exam"; break;
        case TypeLearning::DefaultLearning: return "DefaultLearning"; break;
        case TypeLearning::RepeatWithTimer: return "RepeatWithTimer"; break;
        case TypeLearning::LearnFailedFromRepeat: return "LearnFailedFromRepeat"; break;
        case TypeLearning::LearnFailedFromLearnOrExam: return "LearnFailed"; break;
        default:  return "RepeatDefault"; break;
        }
    }

    return "Session don't started";
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

QString AppEngine::getSessionLasting()
{
    if( currentSession == nullptr)
    {
        return "00:00";
    }

    return currentSession->getSessionLasting().toString("mm:ss");
}

QString AppEngine::getLearningSessionTimerTime()
{
    if( currentSession == nullptr)
    {
        return "00:00";
    }

    return currentSession->getTimerTime().toString("mm:ss");
}

QString AppEngine::getFinishScreenText(){
    if(currentSession!=nullptr)
    {
        Mood currentMood;

        double procPerOneAnswer = 100.0/ (double)(getCountOfRightAnswer() + getCountOfWrongAnswer());
        double wrongAnswersInProc = (double)getCountOfWrongAnswer() * procPerOneAnswer;

        if((wrongAnswersInProc >= procWrongAnswerForBadMood) || //если процент неправильных ответов больше(или равен) порогового
           (getCountOfRightAnswer() == 0 && getCountOfWrongAnswer() == 0))//если ваще ниче не отвечал
            currentMood = Mood::Bad;
        else
            currentMood = Mood::Good;

        return exclamations.getOne(currentMood,currentSession->getCurrentRegime());

    }else
        return "";
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

           emit showMessage("Чтобы учить этот режим нужны билеты, а доступных таких нет. Выбери другой режим.");

           emit finishSession();
           return;
        }

        //emit clearStack();

        onLearnSessionPushFinalPage();

        for(int i=0;i<ticketsToPush.size();i++)
        {
            collectLearningTicket(ticketsToPush[i]);
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

    emit finishSession();
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
    qmlEngine->rootContext()->setContextProperty("listWrongTickets",this->wrongTicketsModel);
}

void AppEngine::onLearnSessionTimeChanged()
{
    emit sessionTimeChanging();
}

void AppEngine::onQmlEngineObjectCreated()
{
    this->bindQMLSlotSignalConnections();
}
