#ifndef TOPIC_H
#define TOPIC_H
#include "theoryimginfo.h"
#include "theoryticketinfo.h"
#include <QList>

class Topic
{
    public:
    int index;
    QString name;
    QString fullText;

    QList <TheoryImgInfo> images;
    QList <TheoryTicketAnswerInfo> ticketAnswers;

    Topic();
};

#endif // TOPIC_H
