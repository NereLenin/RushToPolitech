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

QString Ticket::ticketTypeToString(TicketType type)
{
    switch(type){
    case inputAnswerTicket: return "inputAnswerTicket"; break;
    case selectableAnswerTicket: return "selectableAnswerTicket"; break;
    default: "dontknowntickettype";break;
    }
}

QString Ticket::getStringType(){
    return ticketTypeToString(this->type);
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

int SelectableAnswerTicket::getIndex(){ return index; }

QString SelectableAnswerTicket::getQuestionText(){ return questionText;}

int SelectableAnswerTicket::getIndexOfCorrectAnswer()
{
    return indexOfCorrectAnswer;
}

const QString SelectableAnswerTicket::getAnswer(int index) const {
    if (index < countOfAnswers && index >= 0)
        return answers[index];

    return "";
}

const QString SelectableAnswerTicket::getAnswerImageUrl(int index) const{
    if (index < countOfAnswers && index >= 0)
        return answersImageUrls[index];

    return "";
}

void SelectableAnswerTicket::mixAnswers()
{
    //генерируем случайные числа countOfAnswers
    int shiftNumber = random::randomNumber(0,countOfAnswers);

    int indexOfFirstVictim = random::randomNumber(0,countOfAnswers);
    int indexOfSecondVictim = random::randomNumber(0,countOfAnswers);


    //сдвигаем на случайное количество
    shiftAnswers(shiftNumber);

    //меняем местами два случайных
    swapAnswers(indexOfFirstVictim, indexOfSecondVictim);

    //поднимаем вверх, чтоб нумерация сохранялась
    moveNotVoidAnswersUp();
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


void SelectableAnswerTicket::swapAnswers(int indexFirst, int indexSecond)
{
    if(indexFirst == indexSecond) return;

    //вот тут говной пахнет за версту дядь
    if(indexOfCorrectAnswer == (indexFirst+1))
    {
        indexOfCorrectAnswer = indexSecond+1;
    }
    else if(indexOfCorrectAnswer == indexSecond+1)
    {
        indexOfCorrectAnswer = indexFirst+1;
    }


     QString tempAnswer = answers[indexFirst];
     answers[indexFirst] = answers[indexSecond];
     answers[indexSecond] = tempAnswer;

     tempAnswer = answersImageUrls[indexFirst];
     answersImageUrls[indexFirst] = answersImageUrls[indexSecond];
     answersImageUrls[indexSecond] = tempAnswer;
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

void SelectableAnswerTicket::shiftAnswers(int shiftNumber)
{

    //shiftIndexes{
    QString savedAnswers[countOfAnswers];
    QString savedAnswersUrl[countOfAnswers];

    for(int i=0;i<countOfAnswers;i++)
    {
        savedAnswers[i] = answers[i];
        savedAnswersUrl[i] = answersImageUrls[i];
    }
    //мешаем ответы сдвигом

    //сдвигаем индексы вверх

    int shiftedIndex = 0;
    for(int i = 0; i < countOfAnswers; i++)
    {
        shiftedIndex = i + shiftNumber;

        //-1 т.к в массивах отсчет с нуля
        if(shiftedIndex > (countOfAnswers-1)) shiftedIndex -= countOfAnswers;

        answers[i] = savedAnswers[shiftedIndex];
        answersImageUrls[i] = savedAnswersUrl[shiftedIndex];
    }

    //поскольку двигали вверх перерасчет индекса правильного ответа нужно делать так:
    indexOfCorrectAnswer -= shiftNumber;

    //<1 т.к индекс правильного ответа с 1цы
    if(indexOfCorrectAnswer < 1) indexOfCorrectAnswer += countOfAnswers;

    //}
}

void SelectableAnswerTicket::moveNotVoidAnswersUp()
{
    for(int i =0 ;i < countOfAnswers;i++)
    {
        if(answers[i] == "" && answersImageUrls[i] == "")
        {
            for(int j=i;j<countOfAnswers;j++)
            {
                if(answers[j] != "" || answersImageUrls[j] != "")
                {
                    swapAnswers(i,j);
                    break;
                }
                if(j == (countOfAnswers-1) && (answers[j] == "" && answersImageUrls[j] == ""))
                {  //если добежали до конца и не нашли не пустых ответов
                  //нет смысла бегать дальше первым циклом т.к. дальше только пустота до конца массива
                   return;
                }
            }

        }
    }

}

int SelectableAnswerTicket::getCountOfAnswers() const {
    return countOfAnswers;
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

