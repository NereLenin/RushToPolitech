#ifndef SUBJECT_H
#define SUBJECT_H

#include "topic.h"

class Subject
{
private:
public:
    int index;
    QString name;

    QList <Topic> topics;

    Subject();
};

#endif // SUBJECT_H
