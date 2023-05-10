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
    Q_PROPERTY(QString title READ getTitle CONSTANT)
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

    Q_PROPERTY(QString currentTheoryText  READ getLearningSessionTimerTime CONSTANT)

private:
    const int procWrongAnswerForBadMood = 70;

    QQmlApplicationEngine *qmlEngine;

    TicketBase tickets;
    TheoryBase theory;
    Exclamations exclamations;//база с восклицаниями для финишскрина

    LearnSession *currentSession;//указатель на текущую сессию

    void initialize();//инициализация полей, функция для конструктора
    void bindQMLSlotSignalConnections();//соединяем сигналы/слоты движка и QML

    void connectCurrentSessionWithEngine();//коннект/дисконект сессии с движком
    void disconnectCurrentSessionWithEngine();

    void startLearningSession(LearnSession::TypeLearning regime);//создание учебной сессии

    void emitPushSignalForTicket(Ticket *ticket);//парсим билет и шлем сигнал в QML, чтоб засунуть билет в стек
public:
    explicit AppEngine(QObject *parent = nullptr, QQmlApplicationEngine *qmlEngine = nullptr);

    void connectToEngine(QQmlApplicationEngine *newEngine = nullptr);

    QVariant wrongTicketsModel;//вот об этом хорошенько подумать, модель для листа неправильных билетов

    QVariant learningSubjectsModel;//для списка предметов
    QVariant learningTopicsModel;//для списка предметов
    QVariant topicsTicketModel;//для списка предметов

    //чтука ниже в private надо
    void fillTicketModelFromSession();//ее заполнение/переподключение к движку
    void fillSubjModelFromTheory();
    void fillTopicsModelFromTheory(int subjIndex);
    void fillTopicsTicketModel(int subjIndex,int topicIndex);

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

    //подготавливаем данные для показа предметов
    void onShowSubjects();

    //подготавливаем данные для показа тем
    void onShowTopics(int subjectIndex);

    void onShowTopicsTickets(int subjectIndex, int topicIndex);

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

class TheoryTopicTextController{
private:

public:
    TheoryTopicTextController(Topic &topic){
        currentHighlightStart = 0;
        currentHighlighEnd = 0;

        currentPage = 0;
        countOfPages = 0;

        int textPerPage = 20;//на каждой странице 20 символов
        mainText = topic.getFullText();


        //split string in list with word parts
        int startIndex = 0;
        int indexOfTextPart = 0;

        qDebug() << "----------------------------------------";


        while(startIndex < mainText.length())
        {
            //режем строку и суем ее в лист
            int subStrSize = textPerPage;

            if(startIndex+subStrSize >= mainText.length())
                subStrSize = mainText.length()-startIndex;


            int wordWrapSubSize = subStrSize;
            //расширяем строку до конца слова
            for(;startIndex+wordWrapSubSize < mainText.length() && (mainText[startIndex+wordWrapSubSize] != '\n' && mainText[startIndex+wordWrapSubSize] != ' '); wordWrapSubSize++)
            {
            }

            //записываем
            textes.append(mainText.mid(startIndex,wordWrapSubSize));

            int endIndex = startIndex+wordWrapSubSize;

            //заполняем изображения для нее

            for(int i=0;i<topic.getImages().size();i++){
                if(topic.getImages()[i].positionInText >= startIndex &&
                   topic.getImages()[i].positionInText <= endIndex)
                {
                    imegesInTextParts[indexOfTextPart] = topic.getImages()[i].imageUrl;
                }
            }

            //заполняем ответы с корректировкой индексов

            for(int i=0;i<topic.getTicketAnswers().size();i++){
                  //если в отрывке и начало и конец
                if((topic.getTicketAnswers()[i].getIndexOfStartAnswerInText() >= startIndex &&
                    topic.getTicketAnswers()[i].getIndexOfStartAnswerInText() <= endIndex) &&
                   (topic.getTicketAnswers()[i].getIndexOfEndAnswerInText() >= startIndex &&
                    topic.getTicketAnswers()[i].getIndexOfEndAnswerInText() <= endIndex))
                {
                    int indexOfStartAnswerInTextPart = topic.getTicketAnswers()[i].getIndexOfStartAnswerInText() - startIndex;
                    int indexOfEndAnswerInText = topic.getTicketAnswers()[i].getIndexOfEndAnswerInText() - startIndex;

                    TheoryTicketAnswerInfo currentAnswerInTextPart(topic.getTicketAnswers()[i].getTicketIndex(),indexOfStartAnswerInTextPart, indexOfEndAnswerInText);
                    AnswersInTextParts[indexOfTextPart] = currentAnswerInTextPart;
                }else if(topic.getTicketAnswers()[i].getIndexOfStartAnswerInText() <= startIndex &&
                         topic.getTicketAnswers()[i].getIndexOfEndAnswerInText() >= endIndex){//если только кусок целиком
                    int indexOfStartAnswerInTextPart = 0;
                    int indexOfEndAnswerInText = endIndex - startIndex;//подчеркиваем до конца куска текста

                    TheoryTicketAnswerInfo currentAnswerInTextPart(topic.getTicketAnswers()[i].getTicketIndex(),indexOfStartAnswerInTextPart, indexOfEndAnswerInText);
                    AnswersInTextParts[indexOfTextPart] = currentAnswerInTextPart;

                }//если в куске начало, а конец в каком то следующем
                else if((topic.getTicketAnswers()[i].getIndexOfStartAnswerInText() >= startIndex &&
                         topic.getTicketAnswers()[i].getIndexOfStartAnswerInText() <= endIndex))
                {
                    qDebug() << topic.getTicketAnswers()[i].getIndexOfStartAnswerInText() << "-" << startIndex;
                    int indexOfStartAnswerInTextPart = topic.getTicketAnswers()[i].getIndexOfStartAnswerInText() - startIndex;
                    int indexOfEndAnswerInText = endIndex - startIndex;//подчеркиваем до конца куска текста

                    TheoryTicketAnswerInfo currentAnswerInTextPart(topic.getTicketAnswers()[i].getTicketIndex(),indexOfStartAnswerInTextPart, indexOfEndAnswerInText);
                    AnswersInTextParts[indexOfTextPart] = currentAnswerInTextPart;
                }else if((topic.getTicketAnswers()[i].getIndexOfEndAnswerInText() >= startIndex &&//если в куске только конец
                    topic.getTicketAnswers()[i].getIndexOfEndAnswerInText() <= endIndex))
                {
                    int indexOfStartAnswerInTextPart = 0;//подчеркиваем от самого начала
                    int indexOfEndAnswerInText = topic.getTicketAnswers()[i].getIndexOfEndAnswerInText() - startIndex;

                    TheoryTicketAnswerInfo currentAnswerInTextPart(topic.getTicketAnswers()[i].getTicketIndex(),indexOfStartAnswerInTextPart, indexOfEndAnswerInText);
                    AnswersInTextParts[indexOfTextPart] = currentAnswerInTextPart;
                }
            }

            startIndex = endIndex;
            indexOfTextPart++;
        }

        for(int i = 0; i< textes.size();i++)
        {
            if(imegesInTextParts.contains(i))
            {
                qDebug() << "img" << imegesInTextParts[i];
            }
            if(AnswersInTextParts.contains(i))
            {
                qDebug() << "answers:" << AnswersInTextParts[i].getTicketIndex() << "b:" << AnswersInTextParts[i].getIndexOfStartAnswerInText() << "e:" << AnswersInTextParts[i].getIndexOfEndAnswerInText();
            }

            qDebug() << textes[i];
        }

        qDebug() << "size per page:" << textPerPage << "\n" << textes;
    }

    QString mainText;
    int currentHighlightStart;
    int currentHighlighEnd;

    QString imageUrl;

    int currentPage;
    int countOfPages;

    QList <QString> textes;
    QMap <int,QString> imegesInTextParts;
    QMap <int, TheoryTicketAnswerInfo> AnswersInTextParts;


    void nextPage(){

    }

    void previousPage(){

    }

};

#endif // APPENGINE_H
