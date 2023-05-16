#ifndef THEORYTICKETINFO_H
#define THEORYTICKETINFO_H
#include <QString>

class TheoryTicketAnswerInfo
{
private:
    int ticketIndex;

    int indexOfStartAnswerInText;
    int indexOfEndAnswerInText;
public:
    TheoryTicketAnswerInfo(){
        ticketIndex = indexOfStartAnswerInText = indexOfEndAnswerInText = 0;
    }

    TheoryTicketAnswerInfo(int ticketIndex, int startOfAnswerAt, int endOfAnswerAt);
    TheoryTicketAnswerInfo(QString openTag, int startOfAnswerAt, int endOfAnswerAt);

    int getIndexOfStartAnswerInText() const;
    int getIndexOfEndAnswerInText() const;
    int getTicketIndex() const;
};

#endif // THEORYTICKETINFO_H
