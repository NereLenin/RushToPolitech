#include "subject.h"


const QString &Subject::getName() const
{
    return name;
}

int Subject::getIndex() const
{
    return index;
}

const QList<Topic> &Subject::getTopics() const
{
    return topics;
}

const QString &Subject::getIconUrl() const
{
    return iconUrl;
}

Subject &Subject::operator=(const Subject &subj)
{
    this->setParent(subj.parent());

    this->index = subj.index;
    this->name = subj.name;
    this->iconUrl = subj.iconUrl;

    this->topics = subj.topics;

    return *this;
}

Subject::Subject(QObject *parent) : QObject{parent}
{
    index = 0;
}

Subject::Subject(const Subject &subj): QObject{subj.parent()}
{
    this->index = subj.index;
    this->name = subj.name;
    this->iconUrl = subj.iconUrl;

    this->topics = subj.topics;
}

