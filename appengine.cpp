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
        qDebug() << "Error in main QML page or don't have any";
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

    //соединяем сигнал QML о начале учебной сессии c слотом создания
    //учить сессию
    QObject::connect(rootObject,SIGNAL(startSession(int)),
                     this,SLOT(onStartSession(int)));

    //прогон неправильно отвеченных в ходе сессии билетов
    QObject::connect(rootObject,SIGNAL(startLearnFailedTicketsSession()),
                     this,SLOT(onStartLearnFailedTicketsSession()));

    //прошел все тикеты и дошел до последнего экрана
    QObject::connect(rootObject,SIGNAL(finishLearningSession()),
                     this,SLOT(onFinishLearningSession()));
    //убежал из сессии
    QObject::connect(rootObject,SIGNAL(endLearningSessions()),
                     this,SLOT(onEndLearningSessions()));

    //просит показать предметы
    QObject::connect(rootObject,SIGNAL(showSubjects()),
                     this,SLOT(onShowSubjects()));

    //просит показать темы предмета
    QObject::connect(rootObject,SIGNAL(showTopics(int)),
                     this,SLOT(onShowTopics(int)));


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

void AppEngine::startLearningSession(LearnSession::TypeLearning regime)
{
    if(currentSession != nullptr)
        onEndLearningSessions();

    currentSession = LearnSession::createSession(&tickets,regime);
    connectCurrentSessionWithEngine();
    currentSession->StartSession();//фу блять с большой буквы почему


}

void AppEngine::initialize()
{
    qmlEngine = nullptr;
    currentSession = nullptr;


    LearnSession::initializeTypeLearningForQml();
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

    //qDebug() << theory.getTopicForTicket(1834).fullText;
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
        case LearnSession::Exam: return "Exam"; break;
        case LearnSession::DefaultLearning: return "DefaultLearning"; break;
        case LearnSession::RepeatWithTimer: return "RepeatWithTimer"; break;
        case LearnSession::LearnFailedFromRepeat: return "LearnFailedFromRepeat"; break;
        case LearnSession::LearnFailedFromLearnOrExam: return "LearnFailed"; break;
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

void AppEngine::fillSubjModelFromTheory()
{
    learningSubjectsModel.clear();
    QList <QObject*> modelList;

    for(int i=0;i < theory.getSubjects().size();i++)
         modelList.append(theory.getSubject(i) );

    learningSubjectsModel.setValue(modelList);
}

void AppEngine::fillSubjModelFromTheoryTopics(int subjIndex)
{
    learningSubjectsModel.clear();
    QList <QObject*> modelList;

    Subject *currentSubject = theory.getSubject(subjIndex);
    if(currentSubject == nullptr)
    {
        qDebug() << "fillSubjModelFromTheoryTopics : нет такого предмета ind" << subjIndex;
    }

    for(int i=0;i < currentSubject->topics.size();i++)
    {
        modelList.append(theory.getTopic(subjIndex,i));
    }


    learningSubjectsModel.setValue(modelList);
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
           qDebug() << "Выводим сообщение нулевой билет";
           emit showMessage("Чтобы учить этот режим нужны билеты, а доступных таких нет. Выбери другой режим.");

           emit finishSession();
           return;
        }

        onLearnSessionPushFinalPage();

        for(int i=0;i<ticketsToPush.size();i++)
        {
            collectLearningTicket(ticketsToPush[i]);
        }

}

void AppEngine::onLearnSessionPushFinalPage()
{
        emit pushFinalPage();
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
    qmlEngine->rootContext()->setContextProperty("listWrongTickets",wrongTicketsModel);
}

void AppEngine::onLearnSessionTimeChanged()
{
    emit sessionTimeChanging();
}

void AppEngine::onQmlEngineObjectCreated()
{
    this->bindQMLSlotSignalConnections();
}

void AppEngine::onStartSession(int typeOfLearnSession)
{
    startLearningSession((LearnSession::TypeLearning)typeOfLearnSession);
}

void AppEngine::onShowSubjects()
{
    fillSubjModelFromTheory();
    qmlEngine->rootContext()->setContextProperty("learningSubjectsModel",learningSubjectsModel);
    emit subjectsDataIsReady();
}

void AppEngine::onShowTopics(int subjectIndex)
{
    fillSubjModelFromTheoryTopics(subjectIndex);
    qmlEngine->rootContext()->setContextProperty("learningSubjectsModel",learningSubjectsModel);
    emit topicsDataIsReady();
}
