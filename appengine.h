#ifndef APPENGINE_H
#define APPENGINE_H

#include <QObject>
#include <src/teacher.h>
#include <QQmlApplicationEngine>
#include <QQmlContext>

class AppEngine : public QObject
{

    Q_OBJECT

    Q_PROPERTY(QString title READ getTitle)

    /*
    property int chanceToPassExam: 10
    property int procOfAllLearned: 30
    property int procOfTodayLearned: 10
    */
    Q_PROPERTY(int chanceToPassExam READ getChanceToPassExam)
    Q_PROPERTY(int procOfAllLearned READ getProcOfAllLearned)
    Q_PROPERTY(int procOfTodayLearned READ getProcOfTodayLearned)

    Q_PROPERTY(int allTicketsCount READ getAllTicketsCount)
    Q_PROPERTY(int learnedTicketsCount READ getLearnedTicketsCount)
    Q_PROPERTY(int hardTicketsCount READ getHardTicketsCount)
    Q_PROPERTY(int forgottenTicketsCount READ getForgottenTicketsCount)

private:
    TicketBase base;
    Teacher teacher;

    QQmlApplicationEngine *engine;

    void bindQMLSlotSignalConnections(QObject *rootObject);
public:
    explicit AppEngine(QObject *parent = nullptr, QQmlApplicationEngine *engine = nullptr);

    int getChanceToPassExam()
    {
       return base.getChanceToPassExam();
    }

    int getProcOfAllLearned()
    {
       return base.getAllLearnedProc();
    }

    int getProcOfTodayLearned()
    {
       return base.getTodayLearnedProc();
    }

    int getAllTicketsCount()
    {
       return base.getAllTicketsCount();
    }

    int getLearnedTicketsCount()
    {
       return base.getLearnedTicketsCount();
    }

    int getHardTicketsCount()
    {
       return base.getHardTicketsCount();
    }

    int getForgottenTicketsCount()
    {
       return base.getForgottenTicketsCount();
    }

    QString getTitle()
    {
        return "Yulya is pure sex";
    };

    void emitPushSignalForTicket(Ticket *ticket);
signals:
    void pushSelectable(int index, QString textQuestion, QString pathToImage,
                                   QString variant1Text, QString variant1PathToImg,
                                   QString variant2Text, QString variant2PathToImg,
                                   QString variant3Text, QString variant3PathToImg,
                                   QString variant4Text, QString variant4PathToImg,
                                   int indexOfCorrectVariant);

    void pushInputable(int index, QString correctAnswer, QString textOfQuestion, QString pathToImage);
    void pushStack(QString pageUrl);


public slots:
    void learnController();//отвечает на signal QML startLearningSession

    void onSaveAnswerInStatistic(int index, bool isCorrect);//обработчик qml signal saveAnswerInStatistic
};

#endif // APPENGINE_H
