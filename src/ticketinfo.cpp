#include "ticketinfo.h"

void TicketInfo::resetCounters()
{
    counterOfCorrectAnswers = counterOfWrongAnswers = 0;
}

bool TicketInfo::hasItBeenTwoWeeksFromLastAnswer()
{
    return (dateOfLastAnswer.daysTo(QDate::currentDate()) > 14);
}

void TicketInfo::changeStatus(TicketStatus status)
{
    this->status = status;
    resetCounters();
    dateOfStatusChanged = QDate::currentDate();
}

TicketInfo::TicketInfo(int index)
{
    ticketIndex = index;

    status = TicketStatus::Unlearned;
    counterOfCorrectAnswers = 0;
    counterOfWrongAnswers = 0;

    dateOfLastAnswer = QDate::currentDate();
    dateOfStatusChanged = QDate::currentDate().addDays(-1);
}

TicketInfo *TicketInfo::createTicketInfo(QJsonObject ticketInfo)
{
    TicketInfo *newTicketInfo = new TicketInfo();
    newTicketInfo->ticketIndex = ticketInfo.value("index").toInt();
    newTicketInfo->status = qStringToTicketStatus(ticketInfo.value("status").toString());
    newTicketInfo->counterOfCorrectAnswers = ticketInfo.value("countertOfCorrectAnswers").toInt();
    newTicketInfo->counterOfWrongAnswers = ticketInfo.value("counterOfWrongAnswers").toInt();
    newTicketInfo->dateOfLastAnswer = QDate::fromJulianDay(ticketInfo.value("timeOfLastAnswer").toInt());
    newTicketInfo->dateOfStatusChanged = QDate::fromJulianDay(ticketInfo.value("dateOfStatusChanged").toInt());

    return newTicketInfo;
}

TicketInfo *TicketInfo::createTicketInfo(int index)
{
    TicketInfo *newTicketInfo = new TicketInfo();
    newTicketInfo->ticketIndex = index;
    return newTicketInfo;
}

int TicketInfo::getTicketIndex() const
{
    return ticketIndex;
}

TicketStatus TicketInfo::getTicketStatus() const
{
    return status;
}

QDate TicketInfo::getDateOfLastAnswer() const
{
    return dateOfLastAnswer;
}

QDate TicketInfo::getDateOfStatusChanged() const
{
    return dateOfStatusChanged;
}

void TicketInfo::saveAnswer(TicketAnswerType answer)
{
    dateOfLastAnswer = QDate::currentDate();

    if(answer == TicketAnswerType::Correct)
        counterOfCorrectAnswers++;
    else
        counterOfWrongAnswers++;

    updateStatus();
}

void TicketInfo::updateStatus()
{
    switch(status)
    {
    case TicketStatus::Unlearned:
    {
        if(counterOfWrongAnswers - counterOfCorrectAnswers >= differenceOfAnswersForChangeStatuses)
            changeStatus(TicketStatus::Hard);

        if(counterOfCorrectAnswers - counterOfWrongAnswers  >= differenceOfAnswersForChangeToLearned)
            changeStatus(TicketStatus::Learned);
     }
     break;

    case TicketStatus::Hard:
    {
        if(counterOfCorrectAnswers - counterOfWrongAnswers >= differenceOfAnswersForChangeStatuses)
            changeStatus(TicketStatus::Unlearned);
     }
     break;

    case TicketStatus::Learned:
    {
        if(counterOfWrongAnswers - counterOfCorrectAnswers >= differenceOfAnswersForChangeStatuses)
            changeStatus(TicketStatus::Unlearned);

        if(hasItBeenTwoWeeksFromLastAnswer())
            changeStatus(TicketStatus::Forgotten);
     }
     break;

    case TicketStatus::Forgotten:
    {
        if(!hasItBeenTwoWeeksFromLastAnswer())
        {
            if(counterOfCorrectAnswers > counterOfWrongAnswers)
                changeStatus(TicketStatus::Learned);
            else
                changeStatus(TicketStatus::Unlearned);
        }
     }
     break;

    default:
        qDebug() << "nothing to do with any";
        break;
    };
}

QJsonObject TicketInfo::toJson()
{
    QJsonObject returnItem;

    returnItem["index"] = ticketIndex;
    returnItem["status"] = ticketStatusToQString(status);
    returnItem["counterOfCorrectAnswers"] = counterOfCorrectAnswers;
    returnItem["counterOfWrongAnswers"] = counterOfWrongAnswers;
    returnItem["timeOfLastAnswer"] = dateOfLastAnswer.toJulianDay();
    returnItem["dateOfStatusChanged"] = dateOfStatusChanged.toJulianDay();

        return returnItem;
    }

QString TicketInfo::ticketStatusToQString(TicketStatus status)
{
    switch(status)
    {
        case TicketStatus::Learned: return "Learned"; break;
        case TicketStatus::Unlearned: return "Unlearned"; break;
        case TicketStatus::Hard: return "Hard"; break;
        case TicketStatus::Forgotten: return "Forgotten"; break;
    default: return "Any";
    };
}

TicketStatus TicketInfo::qStringToTicketStatus(QString status)
{
    if(status == "Learned") return TicketStatus::Learned; else
    if(status == "Unlearned") return TicketStatus::Unlearned; else
    if(status == "Hard") return TicketStatus::Hard; else
    if(status == "Forgotten") return TicketStatus::Forgotten;
    else return TicketStatus::Any;
}



