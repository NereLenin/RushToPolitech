#include "tickets.h"

void readJsonArrayToStringArray(QJsonArray array, QString stringArray[4])
{
    for(int i=0;i< array.size();i++)
    {
        stringArray[i] = array[i].toString();
    }
}

Ticket::Ticket(int index)
{
 this->index = index;
}

Ticket *Ticket::createTicket(TicketType type, int index)
{
    switch(type)
    {
     case TicketType::inputAnswerTicket: return new InputAnswerTicket(index); break;
     case TicketType::selectableAnswerTicket: return new SelectableAnswerTicket(index); break;
     default:
        //исключение
        return NULL;
     break;
    };

}


Ticket *Ticket::createTicket(QJsonObject ticket)
{
   Ticket *new_ticket = Ticket::createTicket(qStringToTicketType(ticket.value("type").toString()));
   new_ticket->fillTicketFromJSON(ticket);
   return new_ticket;
}

//QString Ticket::ticketTypeToQString(TicketType status)
//{
//    switch(status){
//    case TicketType::inputAnswerTicket:
//        return "inputAnswerTicket";
//        break;
//    case TicketType::selectableAnswerTicket:
//        return "selectableAnswerTicket";
//        break;
//    default:
//        return "aknowing type";
//        break;
//    };
//}

TicketType Ticket::qStringToTicketType(QString status)
{
    if( status == "inputAnswerTicket")
        return TicketType::inputAnswerTicket;
    else if(status == "selectableAnswerTicket")
        return TicketType::selectableAnswerTicket;

   return TicketType::selectableAnswerTicket;
}

int Ticket::getIndex() const
{
    return index;
}

TicketType Ticket::getType() const
{
    return type;
}

const QString &Ticket::getImageUrl() const
{
    return imageUrl;
}

const QString &Ticket::getQuestionText() const
{
    return questionText;
}

void Ticket::fillTicketFromJSON(QJsonObject ticket)
{
    if(ticket.empty())
    {
        //исключение парс пустой штуки
        qDebug() << "empty JSON ticket";
        return;
    }

    index = ticket.value("index").toInt();
    questionText = ticket.value("text").toString();
    imageUrl = ticket.value("imageURL").toString();
}


/*          selectableAnswerTicket      */
SelectableAnswerTicket::SelectableAnswerTicket(int index) : Ticket(index)
{
    this->type = TicketType::selectableAnswerTicket;
}

int SelectableAnswerTicket::getIndexOfCorrectAnswer()
{
    return indexOfCorrectAnswer;
}

TicketAnswerType SelectableAnswerTicket::isCorrectAnswer(double answer)
{
    if(indexOfCorrectAnswer == answer)
        return TicketAnswerType::Correct;
    else
        return TicketAnswerType::Wrong;
}

TicketAnswerType SelectableAnswerTicket::isCorrectAnswer(QString answer){

    int correctFormAnswerIndex = answer.replace(',','.').toDouble();

    if(correctFormAnswerIndex == indexOfCorrectAnswer)
        return TicketAnswerType::Correct;
    else
        return TicketAnswerType::Wrong;
}


void SelectableAnswerTicket::fillTicketFromJSON(QJsonObject ticket)
{
    Ticket::fillTicketFromJSON(ticket);
    if(type != TicketType::selectableAnswerTicket){
        //исключение несовместимые типы для заполнения
        qDebug() << "wrong types to fill json index:" << this->index;
        return;
    }

    QJsonArray JsonAnswers = ticket.value("answers").toArray();
    readJsonArrayToStringArray(JsonAnswers, answers);

    QJsonArray JsonAnswersImageURL = ticket.value("answersImageURL").toArray();
    readJsonArrayToStringArray(JsonAnswersImageURL, answersImageUrls);

    indexOfCorrectAnswer = ticket.value("correctAnswerIndex").toInt();
}

/*          inputAnswerTicket      */
InputAnswerTicket::InputAnswerTicket(int index): Ticket(index)
{
    this->type = TicketType::inputAnswerTicket;
}

TicketAnswerType InputAnswerTicket::isCorrectAnswer(double answer)
{
    if(QString::number(answer) == correctAnswer)
        return TicketAnswerType::Correct;
    else
        return TicketAnswerType::Wrong;
}

TicketAnswerType InputAnswerTicket::isCorrectAnswer(QString answer)
{
    QString correctDoubleFormOfAnswer = answer.replace(',','.');
    if(correctDoubleFormOfAnswer == correctAnswer)
        return TicketAnswerType::Correct;
    else
        return TicketAnswerType::Wrong;
}

void InputAnswerTicket::fillTicketFromJSON(QJsonObject ticket)
{
    Ticket::fillTicketFromJSON(ticket);

    if(type != TicketType::inputAnswerTicket){
        //исключение несовместимые типы для заполнения
    }
    index = ticket.value("index").toInt();
    questionText = ticket.value("text").toString();

    correctAnswer = (ticket.value("correctAnswer").toString());
    correctAnswer = correctAnswer.replace(',','.');//на случай если ответ число, чтобы привести к double если понадобится
}

QString InputAnswerTicket::getCorrectAnswer()
{
    return correctAnswer;
}

