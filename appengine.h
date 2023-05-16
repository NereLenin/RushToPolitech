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
    Q_PROPERTY(int topicControllerSubjIndex  READ getTopicTextControllerSubjIndex  CONSTANT)
    Q_PROPERTY(int topicControllerTopicIndex READ getTopicTextControllerTopicIndex CONSTANT)
    //вот этих двоих пиздюков сверху наверно можно буит порезать

    //Q_PROPERTY(int currentSubjIndex  READ getСurrentSubjIndex  CONSTANT)
    //Q_PROPERTY(int currentTopicIndex READ getСurrentTopicIndex CONSTANT)

    Q_PROPERTY(QString topicControllerName   READ getTopicTextControllerName NOTIFY topicControllerPageChanged)

    Q_PROPERTY(QString topicControllerMainText  READ getTopicTextControllerText     NOTIFY topicControllerPageChanged)
    Q_PROPERTY(QString topicControllerImageUrl  READ getTopicTextControllerImageUrl NOTIFY topicControllerPageChanged)

    Q_PROPERTY(QString topicControllerSubjIcon  READ getSubjIcon NOTIFY topicControllerPageChanged)

    Q_PROPERTY(int topicControllerHighlightStart  READ getTopicTextControllerCurrentHighlightStart NOTIFY topicControllerPageChanged)
    Q_PROPERTY(int topicControllerHighlighEnd     READ getTopicTextControllerCurrentHighlighEnd    NOTIFY topicControllerPageChanged)

    Q_PROPERTY(int topicControllerCurrentPage   READ getTopicTextControllerCurrentPage  NOTIFY topicControllerPageChanged)
    Q_PROPERTY(int topicControllerCountOfPages  READ getTopicTextControllerCountOfPages NOTIFY topicControllerPageChanged)

private:
    const int procWrongAnswerForBadMood = 70;
    const int sizeOfTextPageInTopic = 200;

    QQmlApplicationEngine *qmlEngine;

    TicketBase tickets;
    TheoryBase theory;
    Exclamations exclamations;//база с восклицаниями для финишскрина

    LearnSession *currentSession;//указатель на текущую сессию
    Topic *currentShowedTopic;

    void initialize();//инициализация полей, функция для конструктора
    void bindQMLSlotSignalConnections();//соединяем сигналы/слоты движка и QML

    void connectCurrentSessionWithEngine();//коннект/дисконект сессии с движком
    void disconnectCurrentSessionWithEngine();

    void startLearningSession(LearnSession::TypeLearning regime);//создание учебной сессии

    void emitPushSignalForTicket(Ticket *ticket);//парсим билет и шлем сигнал в QML, чтоб засунуть билет в стек

    QVariant wrongTicketsModel;//вот об этом хорошенько подумать, модель для листа неправильных билетов
    QVariant learningSubjectsModel;//для списка предметов
    QVariant learningTopicsModel;//для списка предметов
    QVariant topicsTicketModel;//для списка предметов

    //заполнение моделей
    void fillTicketModelFromSession();//ее заполнение/переподключение к движку
    void fillSubjModelFromTheory();
    void fillTopicsModelFromTheory(int subjIndex);
    void fillTopicsTicketModel(int subjIndex,int topicIndex);

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

    //геттеры для темы
    int getСurrentSubjIndex(){
        if(currentShowedTopic!=nullptr) return currentShowedTopic->getSubjectIndex();
        else return 0;
    }

    int getСurrentTopicIndex(){
        if(currentShowedTopic!=nullptr) return currentShowedTopic->getIndex();
        else return 0;
    }

    //геттеры для контроллера чтения темы
    int getTopicTextControllerSubjIndex();
    int getTopicTextControllerTopicIndex();

    QString getTopicTextControllerText();
    QString getTopicTextControllerImageUrl();

    int getTopicTextControllerCurrentHighlightStart();
    int getTopicTextControllerCurrentHighlighEnd();

    int getTopicTextControllerCurrentPage();
    int getTopicTextControllerCountOfPages();

    QString getTopicTextControllerName();
    QString getSubjIcon();

    ~AppEngine(){
        qDebug() << "Деструктор для app Engine";
    }
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
    void topicsTicketsDataIsReady();

    void topicDataIsReady();
    void ticketTopicDataIsReady();

    void topicControllerPageChanged();

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

    //показываем вопросы темы
    void onShowTopicsTickets(int subjectIndex, int topicIndex);
    //показываем содержание темы
    void onShowTopic(int subjectIndex, int topicIndex);

    //билеты темы
    void onShowTopicForTicket(int ticketIndex);

    void onTopicNextPage();
    void onTopicPreviousPage();

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
