#include "topic.h"


const QString &Topic::getFullText() const
{
    return fullText;
}

const QList<TheoryImgInfo> &Topic::getImages() const
{
    return images;
}

const QList<TheoryTicketAnswerInfo> &Topic::getTicketAnswers() const
{
    return ticketAnswers;
}

Topic &Topic::operator =(const Topic &topic)
{
   this->setParent(topic.parent());

    this->index = topic.index;
    this->name = topic.name;
    this->fullText = topic.fullText;
    this->images = topic.images;
    this->ticketAnswers = topic.ticketAnswers;

    return *this;
}

int Topic::getIndex(){
    return index;
}

QString Topic::getName(){
    return name;
}

Topic::Topic(QObject *parent) : QObject{parent}
{
    index = 0;
}

Topic::Topic(const Topic &topic): QObject{topic.parent()}
{
    this->index = topic.index;
    this->name = topic.name;
    this->fullText = topic.fullText;
    this->images = topic.images;
    this->ticketAnswers = topic.ticketAnswers;
}
