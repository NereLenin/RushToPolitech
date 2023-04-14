#ifndef APPENGINE_H
#define APPENGINE_H

#include <QObject>
#include <src/learnsession.h>
#include <exclamations.h>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <src/mytimer.h>
#include <QThread>

class AppEngine : public QObject
{
    Q_OBJECT

    /*  for QML */
    Q_PROPERTY(QString title READ getTitle CONSTANT)
    Q_PROPERTY(QString textOfNullTicket READ getTextOfNullTicket CONSTANT)
    Q_PROPERTY(QString finishScreenText READ getFinishScreenText NOTIFY finishSession)

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

private:
    const QString textOfNullTicket = "Для данного режима билетов больше нет\n Ты чего все выучил шоле?\nНу ты могеш внатуре я в шоке...";
    const int procWrongAnswerForBadMood = 70;

    TicketBase base;
    Exclamations exclamation;

    QQmlApplicationEngine *engine;
    LearnSession *currentSession;

    void connectCurrentSessionWithEngine();
    void disconnectCurrentSessionWithEngine();

    void startLearningSession(TypeLearning regime);

    QMap<TypeLearning,QString> finishScreens;

    QMap<TypeLearning,QString> fillFinishScreens();
    void initialize();
public:

    explicit AppEngine(QQmlApplicationEngine *engine = nullptr,QObject *parent = nullptr);

    const QString getTextOfNullTicket() const;

    void connectToEngine(QQmlApplicationEngine *newEngine = nullptr);

    void bindQMLSlotSignalConnections();

    int getChanceToPassExam();
    int getProcOfAllLearned();
    int getProcOfTodayLearned();
    int getAllTicketsCount();
    int getLearnedTicketsCount();
    int getHardTicketsCount();
    int getForgottenTicketsCount();

    int getCurrentTicketNumber();
    int getCountOfTicketsInSession();


    QString getTitle();

    QVariant wrongTicketsModel;

    void fillTicketModelFromSession();

    int getCountOfRightAnswer();
    int getCountOfWrongAnswer();

    QString getSessionLasting();
    QString getLearningSessionTimerTime();

    QString getFinishScreenText();

    void emitPushSignalForTicket(Ticket *ticket);

signals:
    /* to QML */
    //pushes in stack
    void pushSelectable(int index, QString textQuestion, QString pathToImage,
                                   QString variant1Text, QString variant1PathToImg,
                                   QString variant2Text, QString variant2PathToImg,
                                   QString variant3Text, QString variant3PathToImg,
                                   QString variant4Text, QString variant4PathToImg,
                                   int indexOfCorrectVariant);

    void pushInputable(int index, QString correctAnswer, QString textOfQuestion, QString pathToImage);
    void pushStack(QString pageUrl);
    void clearStack();

    //update properties for QML
    void sessionStatisticChanged();
    void sessionTimeChanging();

    /* To LearningSession */
    void saveStatisticInLearningSession(int index, TicketAnswerType correctness);
    void startLearningFailedTickets();
    void finishSession();

public slots:

    /* QML */
    //контроллеры сессий учебы
    void learnController();//отвечает на signal QML startLearningSession
    void repeatHardController();
    void repeatWithTimerController();
    void repeatRandomController();
    void repeatForgottenController();
    void ExamController();

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

    /*from QMLEngine*/
    void onQmlEngineObjectCreated();
};

#endif // APPENGINE_H
