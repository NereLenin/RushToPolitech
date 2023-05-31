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

    //просит показать подтемы предмета
    QObject::connect(rootObject,SIGNAL(showSubtopics(int,int)),
                     this,SLOT(onShowSubtopics(int,int)));


    //просит показать билеты подтемы
    QObject::connect(rootObject,SIGNAL(showSubtopicTickets(int,int,int)),
                     this,SLOT(onShowSubtopicTickets(int,int,int)));

    //просит показать один билет
    QObject::connect(rootObject,SIGNAL(showSingleTicket(int)),
                     this,SLOT(onShowSingleTicket(int)));

    //показать содержимое подтемы
    QObject::connect(rootObject,SIGNAL(showSubtopic(int,int,int)),
                     this,SLOT(onShowSubtopic(int,int,int)));

    QObject::connect(rootObject,SIGNAL(showSubtopicForTicket(int)),
                     this,SLOT(onShowSubtopicForTicket(int)));

    QObject::connect(rootObject,SIGNAL(subtopicNextPage()),
                     this,SLOT(onSubtopicNextPage()) );

    QObject::connect(rootObject,SIGNAL(subtopicPreviousPage()),
                     this,SLOT(onSubtopicPreviousPage()));

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

    if(regime == LearnSession::LearnTicketsInTopic && currentShowedSubtopic != nullptr)
        currentSession->setCurrentLearnedSubtopic(currentShowedSubtopic);

    connectCurrentSessionWithEngine();
    currentSession->StartSession();//фу блять с большой буквы почему
}

void AppEngine::initialize()
{
    qmlEngine = nullptr;
    currentSession = nullptr;
    currentShowedSubtopic = nullptr;

    //к topic контроллеру
    QObject::connect(&(theory.subtopicController), &TheorySubtopicTextController::pageChanged, this, &AppEngine::onPageChanged);

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
        case LearnSession::LearnTicketsInTopic: return "LearnTicketsInTopic"; break;
        default:  return "RepeatDefault"; break;
        }
    }else{
        return "ShowSingleTicket";
    }

    //return "Session don't started";
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

    for(int i=1;i <= theory.getSubjects().size();i++)
         modelList.append(theory.getSubject(i) );

    learningSubjectsModel.setValue(modelList);
}

void AppEngine::fillTopicsModelFromTheory(int subjIndex)
{

    learningTopicsModel.clear();
    QList <QObject*> modelList;

    Subject *currentSubject = theory.getSubject(subjIndex);
    if(currentSubject == nullptr)
    {
        qDebug() << "fillTopicsModelFromTheory : нет такого предмета ind" << subjIndex;
    }

    for(int i=1;i <= currentSubject->topics.size();i++)
    {
        Topic *currentTopic = theory.getTopic(subjIndex,i);

        if(currentTopic == nullptr){
            qDebug() << "fillTopicsModelFromTheory : нет такой темы" << subjIndex << i;
            return;
        }

        modelList.append(currentTopic);
    }

    learningTopicsModel.setValue(modelList);
}

void AppEngine::fillSubtopicsModelFromTheory(int subjIndex, int topicIndex)
{
    learningSubtopicsModel.clear();
    QList <QObject*> modelList;

    Topic *currentTopic = theory.getTopic(subjIndex,topicIndex);
    if(currentTopic == nullptr)
    {
        qDebug() << "fillSubtopicsModelFromTheory : нет такой темы " << subjIndex << topicIndex;
        return;
    }

    for(int i=1;i <= currentTopic->getSubtopics().size();i++)
    {
        Subtopic *currentSubtopic = theory.getSubtopic(subjIndex,topicIndex,i);

        if(currentSubtopic == nullptr){
            qDebug() << "fillSubtopicsModelFromTheory : нет такой подтемы" << subjIndex << i;
            return;
        }

        modelList.append(currentSubtopic);
    }

    learningSubtopicsModel.setValue(modelList);
}

void AppEngine::fillSubtopicsTicketModel(int subjIndex, int topicIndex, int subjectIndex)
{
    subtopicsTicketModel.clear();
    QList <QObject*> modelList;

    Subtopic *currentSubtopic = theory.getSubtopic(subjIndex,topicIndex,subjectIndex);

    if(currentSubtopic == nullptr)
    {
        qDebug() << "fillTopicsTicketModel : нет такой темы subj" << subjIndex << "topic" << topicIndex;
        return;
    }

    currentShowedSubtopic = currentSubtopic;

    int sizeOfAnswersInTicket = currentSubtopic->getTicketAnswers().size();

    for(int i=0;i < sizeOfAnswersInTicket;i++)
    {
        int indexOfTicket = currentSubtopic->getTicketAnswers()[i].getTicketIndex();
        Ticket *currentTicket = tickets.getTicket(indexOfTicket);
        if(currentTicket == nullptr) continue;

        modelList.append(currentTicket);
    }

    subtopicsTicketModel.setValue(modelList);
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

int AppEngine::getSubtopicTextControllerSubjIndex(){

    if(currentShowedSubtopic != nullptr) return currentShowedSubtopic->getSubjectIndex();
    else return 0;//theory.topicController.getSubjIndex();
}

int AppEngine::getSubtopicTextControllerTopicIndex(){
    if(currentShowedSubtopic != nullptr) return currentShowedSubtopic->getTopicIndex();
    else return 0;
    //return theory.topicController.getTopicIndex();
}

QString AppEngine::getSubtopicTextControllerText(){
    return theory.subtopicController.getMainText();
}

QString AppEngine::getSubtopicTextControllerImageUrl(){
    return theory.subtopicController.getImageUrl();
}

int AppEngine::getSubtopicTextControllerCurrentHighlightStart(){
    return theory.subtopicController.getCurrentHighlightStart();
}

int AppEngine::getSubtopicTextControllerCurrentHighlighEnd(){
    return theory.subtopicController.getCurrentHighlighEnd();
}

int AppEngine::getSubtopicTextControllerCurrentPage(){
    return theory.subtopicController.getCurrentPage();
}

int AppEngine::getSubtopicTextControllerCountOfPages(){
    return theory.subtopicController.countOfPages();
}

QString AppEngine::getSubtopicTextControllerName(){
    return theory.subtopicController.getName();
}

QString AppEngine::getSubjIcon(){

    Subject *currentSubject = theory.getSubject(getSubtopicTextControllerSubjIndex());

    if(currentSubject!=nullptr)
    {
        return currentSubject->getIconUrl();
    }

    return "";
}

AppEngine::~AppEngine(){
    qDebug() << "Деструктор для app Engine";
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
    qDebug() << "BACK END SESSION";
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
    qDebug() << "BACK FINISH SESSION";
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

void AppEngine::onShowSingleTicket(int ticketIndex)
{
    Ticket* showTicket = tickets.getTicket(ticketIndex);
    if(showTicket != nullptr) collectLearningTicket(showTicket);
}

void AppEngine::onShowSubjects()
{
    onEndLearningSessions();

    fillSubjModelFromTheory();
    qmlEngine->rootContext()->setContextProperty("learningSubjectsModel",learningSubjectsModel);
    emit subjectsDataIsReady();
}

void AppEngine::onShowTopics(int subjectIndex)
{
    onEndLearningSessions();

    fillTopicsModelFromTheory(subjectIndex);//-1
    qmlEngine->rootContext()->setContextProperty("learningTopicsModel",learningTopicsModel);
    emit topicsDataIsReady();
}

void AppEngine::onShowSubtopics(int subjectIndex, int topicIndex)
{
    fillSubtopicsModelFromTheory(subjectIndex,topicIndex);//-1
    qmlEngine->rootContext()->setContextProperty("learningSubtopicsModel",learningSubtopicsModel);
    emit subtopicsDataIsReady();
}

void AppEngine::onShowSubtopicTickets(int subjectIndex, int topicIndex, int subtopicIndex)
{
    fillSubtopicsTicketModel(subjectIndex,topicIndex,subtopicIndex);//-1 -1
    qmlEngine->rootContext()->setContextProperty("subtopicsTicketModel",subtopicsTicketModel);
    emit subtopicTicketsDataIsReady();
}

void AppEngine::onShowSubtopic(int subjectIndex, int topicIndex, int subtopicIndex){

    Subtopic *currentSubtopic = theory.getSubtopic(subjectIndex,topicIndex,subtopicIndex);

    if(currentSubtopic != nullptr)
    {
        currentShowedSubtopic = currentSubtopic;//сохраняем текущий просматриваемую тему
        theory.subtopicController.setSubtopic(*currentSubtopic,sizeOfTextPageInTopic);
        emit subtopicDataIsReady();
    }
}


void AppEngine::onShowSubtopicForTicket(int ticketIndex){
    Ticket *neededTicket = tickets.getTicket(ticketIndex);

    if(neededTicket != nullptr)
    {
        Subtopic *subtopicForTicket = theory.getSubtopicForTicket(ticketIndex);
        if(subtopicForTicket != nullptr)
        {
            theory.subtopicController.setSubtopic(*subtopicForTicket,sizeOfTextPageInTopic);
            theory.subtopicController.showAnswerTicket(neededTicket->getIndex());
            emit ticketSubtopicDataIsReady();
        }

    }
}

void AppEngine::onSubtopicNextPage(){
    theory.subtopicController.nextPage();
}

void AppEngine::onSubtopicPreviousPage(){
    theory.subtopicController.previousPage();
}

void AppEngine::onPageChanged(){
    emit subtopicControllerPageChanged();
}


