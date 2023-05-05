#ifndef THEORYTICKETINFO_H
#define THEORYTICKETINFO_H
#include <QString>

class TheoryTicketAnswerInfo
{
private:
    public:
    int ticketIndex;

    int indexOfStartAnswerInText;
    int indexOfEndAnswerInText;

    TheoryTicketAnswerInfo(int ticketIndex, int startOfAnswerAt, int endOfAnswerAt);
    TheoryTicketAnswerInfo(QString openTag, int startOfAnswerAt, int endOfAnswerAt);

    int getIndexOfStartAnswerInText() const;
    int getIndexOfEndAnswerInText() const;
    int getTicketIndex() const;
};

#endif // THEORYTICKETINFO_H
