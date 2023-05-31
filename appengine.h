#ifndef APPENGINE_H
#define APPENGINE_H

#include <QObject>

#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QThread>

#include "src/mytimer.h"

#include "src/learnsession.h"
#include "exclamations.h"
#include "src/theory/theorybase.h"



class AppEngine : public QObject
{
    Q_OBJECT

    /*  for QML */
    Q_PROPERTY(QString title                READ getTitle                CONSTANT)
    Q_PROPERTY(QString finishScreenText     READ getFinishScreenText     NOTIFY finishSession)
    Q_PROPERTY(QString typeOfCurrentSession READ getTypeOfCurrentSession NOTIFY sessionStatisticChanged)
    //currentSubjectIcon

    // statistic
    Q_PROPERTY(int chanceToPassExam   READ getChanceToPassExam   NOTIFY sessionStatisticChanged)
    Q_PROPERTY(int procOfAllLearned   READ getProcOfAllLearned   NOTIFY sessionStatisticChanged)
    Q_PROPERTY(int procOfTodayLearned READ getProcOfTodayLearned NOTIFY sessionStatisticChanged)

    Q_PROPERTY(int allTicketsCount       READ getAllTicketsCount       NOTIFY sessionStatisticChanged)
    Q_PROPERTY(int learnedTicketsCount   READ getLearnedTicketsCount   NOTIFY sessionStatisticChanged)
    Q_PROPERTY(int hardTicketsCount      READ getHardTicketsCount      NOTIFY sessionStatisticChanged)
    Q_PROPERTY(int forgottenTicketsCount READ getForgottenTicketsCount NOTIFY sessionStatisticChanged)

    //learning session
    Q_PROPERTY(int currentTicketNumber       READ getCurrentTicketNumber     NOTIFY sessionStatisticChanged)
    Q_PROPERTY(int countOfTicketsInSession   READ getCountOfTicketsInSession CONSTANT)

    Q_PROPERTY(int countRightAnswer   READ getCountOfRightAnswer NOTIFY finishSession)
    Q_PROPERTY(int countWrongAnswer   READ getCountOfWrongAnswer NOTIFY finishSession)

    Q_PROPERTY(QString sessionLasting   READ getSessionLasting           NOTIFY finishSession)
    Q_PROPERTY(QString timerTime        READ getLearningSessionTimerTime NOTIFY sessionTimeChanging)

    //Q_PROPERTY(QString currentTheoryText  READ getLearningSessionTimerTime CONSTANT)

    //topic text controller
    Q_PROPERTY(int subtopicControllerSubjIndex  READ getSubtopicTextControllerSubjIndex  CONSTANT)
    Q_PROPERTY(int subtopicControllerTopicIndex READ getSubtopicTextControllerTopicIndex CONSTANT)
    Q_PROPERTY(int subtopicControllerSubtopicIndex READ getSubtopicTextControllerSubtopicIndex CONSTANT)

    Q_PROPERTY(QString subtopicControllerName   READ getSubtopicTextControllerName NOTIFY subtopicControllerPageChanged)

    Q_PROPERTY(QString subtopicControllerMainText  READ getSubtopicTextControllerText     NOTIFY subtopicControllerPageChanged)
    Q_PROPERTY(QString subtopicControllerImageUrl  READ getSubtopicTextControllerImageUrl NOTIFY subtopicControllerPageChanged)

    Q_PROPERTY(QString subtopicControllerSubjIcon  READ getSubjIcon NOTIFY subtopicControllerPageChanged)

    Q_PROPERTY(int subtopicControllerHighlightStart  READ getSubtopicTextControllerCurrentHighlightStart NOTIFY subtopicControllerPageChanged)
    Q_PROPERTY(int subtopicControllerHighlighEnd     READ getSubtopicTextControllerCurrentHighlighEnd    NOTIFY subtopicControllerPageChanged)

    Q_PROPERTY(int subtopicControllerCurrentPage   READ getSubtopicTextControllerCurrentPage  NOTIFY subtopicControllerPageChanged)
    Q_PROPERTY(int subtopicControllerCountOfPages  READ getSubtopicTextControllerCountOfPages NOTIFY subtopicControllerPageChanged)

private:
    const int procWrongAnswerForBadMood = 70;
    const int sizeOfTextPageInTopic = 200;

    QQmlApplicationEngine *qmlEngine;

    TicketBase tickets;
    TheoryBase theory;
    Exclamations exclamations;//база с восклицаниями для финишскрина

    LearnSession *currentSession;//указатель на текущую сессию
    Subtopic *currentShowedSubtopic;

    void initialize();//инициализация полей, функция для конструктора
    void bindQMLSlotSignalConnections();//соединяем сигналы/слоты движка и QML

    void connectCurrentSessionWithEngine();//коннект/дисконект сессии с движком
    void disconnectCurrentSessionWithEngine();

    void startLearningSession(LearnSession::TypeLearning regime);//создание учебной сессии

    void emitPushSignalForTicket(Ticket *ticket);//парсим билет и шлем сигнал в QML, чтоб засунуть билет в стек

    QVariant wrongTicketsModel;//вот об этом хорошенько подумать, модель для листа неправильных билетов
    QVariant learningSubjectsModel;//для списка предметов
    QVariant learningTopicsModel;//для списка тем
    QVariant learningSubtopicsModel;//для списка тем

    QVariant subtopicsTicketModel;//для списка предметов

    //заполнение моделей
    void fillTicketModelFromSession();//ее заполнение/переподключение к движку
    void fillSubjModelFromTheory();
    void fillTopicsModelFromTheory(int subjIndex);
    void fillSubtopicsModelFromTheory(int subjIndex,int topicIndex);
    void fillSubtopicsTicketModel(int subjIndex,int topicIndex, int subjectIndex);

public:
    explicit AppEngine(QObject *parent = nullptr, QQmlApplicationEngine *qmlEngine = nullptr);

    void connectToEngine(QQmlApplicationEngine *newEngine = nullptr);

    //Геттеры для QML
    const QString getTitle() const;

    QString getTypeOfCurrentSession();

    //геттеры статистики для QML
    int getChanceToPassExam();
    int getProcOfAllLearned();
    int getProcOfTodayLearned();
    int getAllTicketsCount();
    int getLearnedTicketsCount();
    int getHardTicketsCount();
    int getForgottenTicketsCount();

    //геттеры для хэдера QML, конкретно эти два - для экзамена
    int getCurrentTicketNumber();
    int getCountOfTicketsInSession();

    //геттеры для финиш скрина
    QString getFinishScreenText();

    int getCountOfRightAnswer();
    int getCountOfWrongAnswer();

    QString getSessionLasting();
    QString getLearningSessionTimerTime();

    //геттеры для контроллера чтения темы
    int getSubtopicTextControllerSubjIndex();
    int getSubtopicTextControllerTopicIndex();
    int getSubtopicTextControllerSubtopicIndex(){
        if(currentShowedSubtopic != nullptr) return currentShowedSubtopic->getIndex();
        else return 0;
    }

    QString getSubtopicTextControllerText();
    QString getSubtopicTextControllerImageUrl();

    int getSubtopicTextControllerCurrentHighlightStart();
    int getSubtopicTextControllerCurrentHighlighEnd();

    int getSubtopicTextControllerCurrentPage();
    int getSubtopicTextControllerCountOfPages();

    QString getSubtopicTextControllerName();
    QString getSubjIcon();

    ~AppEngine();
signals:
    /* to QML */
    void collectLearningTicket(Ticket *ticketItem);
    void pushFinalPage();

    void showMessage(QString textOfMessage);

    //update properties for QML
    void sessionStatisticChanged();
    void sessionTimeChanging();

    //for theory
    void subjectsDataIsReady();
    void topicsDataIsReady();
    void subtopicsDataIsReady();

    void subtopicTicketsDataIsReady();//билеты в подтеме
    void ticketSubtopicDataIsReady();//когда учим билет и вызываем тему для него

    void subtopicDataIsReady();//когда готово содержимое подтемы

    void subtopicControllerPageChanged();

    /* To LearningSession */
    void saveStatisticInLearningSession(int index, TicketAnswerType correctness);
    void startLearningFailedTickets();

    //посылаем в учебную сессию сигнал, что в QML дошли до последнего экрана
    void finishSession();
private slots:
    /*from QMLEngine*/
    void onQmlEngineObjectCreated();

    /* QML */
    //контроллер сессий учебы
    void onStartSession(int typeOfLearnSession);
    void onShowSingleTicket(int ticketIndex);

    /* theory */
    //подготавливаем данные для показа предметов
    void onShowSubjects();

    //подготавливаем данные для показа тем
    void onShowTopics(int subjectIndex);

    //подготавливаем данные для показа подтем
    void onShowSubtopics(int subjectIndex, int topicIndex);

    //показываем вопросы подтемы
    void onShowSubtopicTickets(int subjectIndex, int topicIndex, int subtopicIndex);

    //показываем содержание подтемы
    void onShowSubtopic(int subjectIndex, int topicIndex, int subtopicIndex);

    //для билета показыавем подтему
    void onShowSubtopicForTicket(int ticketIndex);

    void onSubtopicNextPage();
    void onSubtopicPreviousPage();

    void onPageChanged();


    /*Learning*/
    //окончание учебной сессии (сьебался в процессе или ушел с экрана с результатами)
    void onEndLearningSessions();

    //прошел все тикеты и дошел до экрана со статистикой
    void onFinishLearningSession();

    //переименовать onQMLSaveAnswerInStatistic
    void onSaveAnswerInStatistic(int index, bool isCorrect);//Зеркало с QML в LearningSession

    //слот для сигнала о начале повтора неправильных билетов
    void onStartLearnFailedTicketsSession();

    /*from Learning Session*/
    void onLearnSessionFillStack(QList <Ticket*> ticketsToPush);
    void onLearnSessionPushFinalPage();

    void onLearnSessionStatisticChanged();
    void onLearnSessionTimeChanged();

};

#endif // APPENGINE_H
