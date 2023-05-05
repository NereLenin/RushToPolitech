#include "theoryticketinfo.h"



int TheoryTicketAnswerInfo::getTicketIndex() const
{
    return ticketIndex;
}

TheoryTicketAnswerInfo::TheoryTicketAnswerInfo(int ticketIndex, int startOfAnswerAt, int endOfAnswerAt)
{
    this->ticketIndex = ticketIndex;
    indexOfStartAnswerInText = startOfAnswerAt;
    indexOfEndAnswerInText = endOfAnswerAt;
}

TheoryTicketAnswerInfo::TheoryTicketAnswerInfo(QString openTag, int startOfAnswerAt, int endOfAnswerAt)
{
    int newTicketIndex = openTag.remove("<begin answer for ").remove(">").remove(" ").toInt();
    TheoryTicketAnswerInfo(newTicketIndex,startOfAnswerAt,endOfAnswerAt);
}

int TheoryTicketAnswerInfo::getIndexOfStartAnswerInText() const
{
    return indexOfStartAnswerInText;
}

int TheoryTicketAnswerInfo::getIndexOfEndAnswerInText() const
{
    return indexOfEndAnswerInText;
}


