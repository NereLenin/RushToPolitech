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
    Q_PROPERTY(QString typeOfCurrentSession READ getTypeOfCurrentSession NOTIFY sessionStatisticChanged)

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

    QQmlApplicationEngine *qmlEngine;

    TicketBase tickets;
    Exclamations exclamations;//база с восклицаниями для финишскрина

    LearnSession *currentSession;//указатель на текущую сессию

    QMap<TypeLearning,QString> finishScreens;//таблица для финишскринов/относительно сессии

    void initialize();//инициализация полей, функция для конструктора
    void bindQMLSlotSignalConnections();//соединяем сигналы/слоты движка и QML

    void connectCurrentSessionWithEngine();//коннект/дисконект сессии с движком
    void disconnectCurrentSessionWithEngine();

    void startLearningSession(TypeLearning regime);//создание учебной сессии

    QMap<TypeLearning,QString> fillFinishScreens();//заполнение

    void emitPushSignalForTicket(Ticket *ticket);//парсим билет и шлем сигнал в QML, чтоб засунуть билет в стек
public:
    explicit AppEngine(QObject *parent = nullptr, QQmlApplicationEngine *qmlEngine = nullptr);

    void connectToEngine(QQmlApplicationEngine *newEngine = nullptr);

    QVariant wrongTicketsModel;//вот об этом хорошенько подумать, модель для листа неправильных билетов
    void fillTicketModelFromSession();//ее заполнение/переподключение к движку

    //Геттеры для QML
    const QString getTextOfNullTicket() const;
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

    void showMessage(QString textOfMessage);

    //update properties for QML
    void sessionStatisticChanged();
    void sessionTimeChanging();

    /* To LearningSession */
    void saveStatisticInLearningSession(int index, TicketAnswerType correctness);
    void startLearningFailedTickets();

    //посылаем в учебную сессию сигнал, что в QML дошли до последнего экрана
    void finishSession();
public slots:
    /*from QMLEngine*/
    void onQmlEngineObjectCreated();

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
};

#endif // APPENGINE_H
