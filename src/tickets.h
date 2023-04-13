#ifndef TICKETS_H
#define TICKETS_H

#include <QString>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>
#include <QRandomGenerator>

enum TicketType {selectableAnswerTicket, inputAnswerTicket};
enum TicketAnswerType{Wrong,Correct};

class Ticket: public QObject
{
    Q_OBJECT

    Q_PROPERTY(int ticketIndex READ getIndex CONSTANT)
    Q_PROPERTY(QString questionText READ getQuestionText CONSTANT)
protected:
    int index;
    TicketType type;
    QString imageUrl;
    QString questionText;

    virtual void fillTicketFromJSON(QJsonObject ticket);

    Ticket(QObject *parent = nullptr, int index = 0);//can't create object for this class

public:
    static Ticket* createTicket(TicketType type, int index =0);
    static Ticket* createTicket(QJsonObject ticket, int index =0);

    static TicketType qStringToTicketType(QString status);

    int getIndex() const;
    TicketType getType() const;
    const QString &getImageUrl() const;
    const QString &getQuestionText() const;

    virtual TicketAnswerType isCorrectAnswer(double answer) =0;
    virtual TicketAnswerType isCorrectAnswer(QString answer) = 0;

    virtual ~Ticket(){}

    //----------debugFunc
    virtual void debugPrint() const{
        qDebug() << "\n----------------";
        qDebug() << "index: " << index ;
        switch(type){
        case selectableAnswerTicket:
            qDebug() << " type: selectableAnswerTicket";
            break;
        case inputAnswerTicket:
            qDebug() << " type: inputAnswerTicket";
            break;
        default:
            qDebug() << " type: неизвестный тип";
            break;
        }
        qDebug() << " imageURL: " << imageUrl;
        qDebug() << " questText: " << questionText;

    }
};


class SelectableAnswerTicket : public Ticket
{
    Q_OBJECT

    Q_PROPERTY(int ticketIndex READ getIndex CONSTANT)
    Q_PROPERTY(QString questionText READ getQuestionText CONSTANT)

public: const static int countOfAnswers = 4;

private:
    QString answers[countOfAnswers];
    QString answersImageUrls[countOfAnswers];
    int indexOfCorrectAnswer;



    void fillTicketFromJSON(QJsonObject ticket);

    void swapAnswers(int indexFirst, int indexSecond);
    void shiftAnswers(int shiftNumber);
    void moveNotVoidAnswersUp();
public:


    SelectableAnswerTicket(int index = 0);

    int getIndex(){ return index; }
    QString getQuestionText(){ return questionText;}

    int getIndexOfCorrectAnswer();//убрать?

    const QString getAnswer(int index) const;

    const QString getAnswerImageUrl(int index) const;

    void mixAnswers();

    virtual TicketAnswerType isCorrectAnswer(double answer);
    virtual TicketAnswerType isCorrectAnswer(QString answer);

    //----------debugFunc
    void debugPrint() const {
        Ticket::debugPrint();
        for(int i=0; i< countOfAnswers;i++)
            qDebug() << " answers[" << i << "]: " << answers[i] ;

        for(int i=0; i< countOfAnswers;i++)
            qDebug() << " answersImgURL[" << i << "]: " << answersImageUrls[i] ;

        qDebug() << " indexOfCorrAnswer:" << indexOfCorrectAnswer;
    }
    ~SelectableAnswerTicket(){}
};


class InputAnswerTicket : public Ticket
{
    Q_OBJECT

    Q_PROPERTY(int ticketIndex READ getIndex CONSTANT)
    Q_PROPERTY(QString questionText READ getQuestionText CONSTANT)

private:
   QString correctAnswer;

   void fillTicketFromJSON(QJsonObject ticket);
public:
   InputAnswerTicket(int index = 0);

   virtual TicketAnswerType isCorrectAnswer(double answer);
   virtual TicketAnswerType isCorrectAnswer(QString answer);

   int getIndex(){ return index; }
   QString getQuestionText(){ return questionText;}

   QString getCorrectAnswer(); //убрать?
   //----------debugFunc
   void debugPrint() const {
       Ticket::debugPrint();

       qDebug() << " correctAnswer:" << correctAnswer;
   }
   ~InputAnswerTicket(){}
};

#endif // TICKETS_H
