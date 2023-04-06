#ifndef APPENGINE_H
#define APPENGINE_H

#include <QObject>
#include <src/teacher.h>
#include <src/learnsession.h>
#include <QQmlApplicationEngine>
#include <QQmlContext>

class AppEngine : public QObject
{

    Q_OBJECT

    /*  for QML */

    Q_PROPERTY(QString title READ getTitle)

    // statistic
    Q_PROPERTY(int chanceToPassExam   READ getChanceToPassExam)
    Q_PROPERTY(int procOfAllLearned   READ getProcOfAllLearned)
    Q_PROPERTY(int procOfTodayLearned READ getProcOfTodayLearned)

    Q_PROPERTY(int allTicketsCount       READ getAllTicketsCount)
    Q_PROPERTY(int learnedTicketsCount   READ getLearnedTicketsCount)
    Q_PROPERTY(int hardTicketsCount      READ getHardTicketsCount)
    Q_PROPERTY(int forgottenTicketsCount READ getForgottenTicketsCount)

    //learning session
    Q_PROPERTY(int countRightAnswer   READ getCountOfRightAnswer NOTIFY sessionStatisticChanged)
    Q_PROPERTY(int countWrongAnswer   READ getCountOfWrongAnswer NOTIFY sessionStatisticChanged)

    //models
    Q_PROPERTY(QVariant wrongTicketsModel READ getWrongTicketsModel NOTIFY sessionStatisticChanged)

private:
    TicketBase base;
    Teacher teacher;

    QQmlApplicationEngine *engine;
    LearnSession *currentSession;

    void bindQMLSlotSignalConnections(QObject *rootObject);

    void connectCurrentSessionWithEngine();
    void disconnectCurrentSessionWithEngine();

    void startLearningSession(TypeLearning regime);
    
public:
    explicit AppEngine(QObject *parent = nullptr, QQmlApplicationEngine *engine = nullptr);

    int getChanceToPassExam();
    int getProcOfAllLearned();
    int getProcOfTodayLearned();
    int getAllTicketsCount();
    int getLearnedTicketsCount();
    int getHardTicketsCount();
    int getForgottenTicketsCount();
    QString getTitle();

    QVariant getWrongTicketsModel()
    {
        QList <QObject*> modelList;
        if(currentSession != nullptr)
        {
            for(int i=0;i<currentSession->getListOfWrongTicket().size();i++)
                modelList.append((currentSession->getListOfWrongTicket())[i]);
        }

    return QVariant::fromValue(modelList);
    }

    int getCountOfRightAnswer();
    int getCountOfWrongAnswer();

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

    //update properties
    void sessionStatisticChanged();

    /* To LearningSession */
    void saveStatisticInLearningSession(int index, TicketAnswerType correctness);


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

    //переименовать onQMLSaveAnswerInStatistic
    void onSaveAnswerInStatistic(int index, bool isCorrect);//Зеркало с QML в LearningSession

    /*from Learning Session*/
    void onLearnSessionFillStack(QList <Ticket*> ticketsToPush, QString finalScreen);
    void onLearnSessionStatisticChanged();
};

#endif // APPENGINE_H
