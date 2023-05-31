#include "topic.h"



Topic &Topic::operator =(const Topic &topic)
{
   this->setParent(topic.parent());

    //operator = ?
    this->subjectIndex = topic.subjectIndex;
    this->index = topic.index;

    this->name = topic.name;
    subtopics = topic.subtopics;

    return *this;
}

int Topic::getSubjectIndex() const
{
    return subjectIndex;
}

QList<Subtopic> &Topic::getSubtopics()
{
    return subtopics;
}

int Topic::getIndex(){
    return index;
}

QString Topic::getName(){
    return name;
}

Topic::Topic(QObject *parent) : QObject{parent}
{
    subjectIndex = 0;
    index = 0;
}

Topic::Topic(const Topic &topic): QObject{topic.parent()}
{
    this->subjectIndex = topic.subjectIndex;
    this->index = topic.index;
    this->name = topic.name;
    subtopics = topic.subtopics;
}
