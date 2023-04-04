#ifndef TICKETS_H
#define TICKETS_H
#include <QString>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>

enum TicketType {selectableAnswerTicket, inputAnswerTicket};
enum TicketAnswerType{Wrong,Correct};

class Ticket
{
protected:
    int index;
    TicketType type;
    QString imageUrl;
    QString questionText;

    virtual void fillTicketFromJSON(QJsonObject ticket);

    Ticket(int index = 0);//can't create object for this class

public:
    static Ticket* createTicket(TicketType type, int index =0);
    static Ticket* createTicket(QJsonObject ticket);

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
private:
    QString answers[4];
    QString answersImageUrls[4];
    int indexOfCorrectAnswer;

    void fillTicketFromJSON(QJsonObject ticket);
public:
    SelectableAnswerTicket(int index = 0);

    int getIndexOfCorrectAnswer();//убрать?

    const QString getAnswer(int index) const {
        if (index < 4 && index >= 0)
            return answers[index];

        return "";
    }

    const QString getAnswerImageUrl(int index) const{
        if (index < 4 && index >= 0)
            return answersImageUrls[index];

        return "";
    }

    virtual TicketAnswerType isCorrectAnswer(double answer);
    virtual TicketAnswerType isCorrectAnswer(QString answer);

    //----------debugFunc
    void debugPrint() const {
        Ticket::debugPrint();
        for(int i=0; i< 4;i++)
            qDebug() << " answers[" << i << "]: " << answers[i] ;

        for(int i=0; i< 4;i++)
            qDebug() << " answersImgURL[" << i << "]: " << answersImageUrls[i] ;

        qDebug() << " indexOfCorrAnswer:" << indexOfCorrectAnswer;
    }
};


class InputAnswerTicket : public Ticket
{
private:
   QString correctAnswer;

   void fillTicketFromJSON(QJsonObject ticket);
public:
   InputAnswerTicket(int index = 0);

   virtual TicketAnswerType isCorrectAnswer(double answer);
   virtual TicketAnswerType isCorrectAnswer(QString answer);


   QString getCorrectAnswer(); //убрать?
   //----------debugFunc
   void debugPrint() const {
       Ticket::debugPrint();

       qDebug() << " correctAnswer:" << correctAnswer;
   }
};

#endif // TICKETS_H
