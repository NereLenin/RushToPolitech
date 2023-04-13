#include "tickets.h"

void readJsonArrayToStringArray(QJsonArray array, QString stringArray[4])
{
    for(int i=0;i< array.size();i++)
    {
        stringArray[i] = array[i].toString();
    }
}

Ticket::Ticket(QObject *parent, int index): QObject{parent}
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


Ticket *Ticket::createTicket(QJsonObject ticket, int index)
{
   Ticket *new_ticket = Ticket::createTicket(qStringToTicketType(ticket.value("type").toString()),index);
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
    questionText = ticket.value("text").toString();
    imageUrl = ticket.value("imageURL").toString();
}


/*          selectableAnswerTicket      */
SelectableAnswerTicket::SelectableAnswerTicket(int index) : Ticket(nullptr,index)
{
    this->type = TicketType::selectableAnswerTicket;
}

int SelectableAnswerTicket::getIndexOfCorrectAnswer()
{
    return indexOfCorrectAnswer;
}

const QString SelectableAnswerTicket::getAnswer(int index) const {
    if (index < 4 && index >= 0)
        return answers[index];

    return "";
}

const QString SelectableAnswerTicket::getAnswerImageUrl(int index) const{
    if (index < 4 && index >= 0)
        return answersImageUrls[index];

    return "";
}

void SelectableAnswerTicket::mixAnswers()
{
    qDebug() << "origin:";
    this->debugPrint();
    QString savedAnswers[4];
    QString savedAnswersUrl[4];

    for(int i=0;i<4;i++)
    {
        savedAnswers[i] = answers[i];
        savedAnswersUrl[i] = answersImageUrls[i];
    }
    //мешаем ответы сдвигом
    QRandomGenerator *randomGenerator = QRandomGenerator::global();

    int shiftNumber = 1;//randomGenerator->bounded(0,4);

    //shiftим индексы

    int shiftedIndex = 0;
    for(int i = 0; i < 4; i++)
    {
        shiftedIndex = i + shiftNumber;
        if(shiftedIndex > 3) shiftedIndex -= 4;

        answers[i] = savedAnswers[shiftedIndex];
        answersImageUrls[i] = savedAnswersUrl[shiftedIndex];
    }

    qDebug() << "был индекс: " << indexOfCorrectAnswer;
    indexOfCorrectAnswer -= shiftNumber;
    if(indexOfCorrectAnswer < 1) indexOfCorrectAnswer += 4;
    qDebug() << "теперь:" << indexOfCorrectAnswer;

    //конец сдвига
    qDebug() << "after shift:";
    this->debugPrint();

    //меняем одну сладкую парочку
    int indexOfFirstVictim = randomGenerator->bounded(0,4);

    randomGenerator = nullptr;

    int indexOfSecondVictim = indexOfFirstVictim + shiftNumber;

    if(indexOfSecondVictim > 3) indexOfSecondVictim -= 4;

    //вот тут говной пахнет за версту дядь
    if(indexOfCorrectAnswer == (indexOfFirstVictim+1))
    {
        indexOfCorrectAnswer = indexOfSecondVictim+1;
    }
    else if(indexOfCorrectAnswer == indexOfSecondVictim+1)
    {
        indexOfCorrectAnswer = indexOfFirstVictim+1;
    }


     QString tempAnswer = answers[indexOfFirstVictim];
     answers[indexOfFirstVictim] = answers[indexOfSecondVictim];
     answers[indexOfSecondVictim] = tempAnswer;

     tempAnswer = answersImageUrls[indexOfFirstVictim];
     answersImageUrls[indexOfFirstVictim] = answersImageUrls[indexOfSecondVictim];
     answersImageUrls[indexOfSecondVictim] = tempAnswer;

     qDebug() << "after swap:";
     this->debugPrint();

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
InputAnswerTicket::InputAnswerTicket(int index): Ticket(nullptr,index)
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
    correctAnswer = (ticket.value("correctAnswer").toString());
    correctAnswer = correctAnswer.replace(',','.');//на случай если ответ число, чтобы привести к double если понадобится
}

QString InputAnswerTicket::getCorrectAnswer()
{
    return correctAnswer;
}

