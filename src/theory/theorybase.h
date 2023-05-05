#ifndef THEORYBASE_H
#define THEORYBASE_H
#include "subject.h"
#include "theorybasereader.h"

class TheoryBase
{
private:
    QList <Subject> subjects;
public:
    TheoryBase(QString pathToJsonDB = ":/ticketBase/TheoryBase.json");
    void clear();

    Subject getSubject(int index);

    Topic getTopic(int subjectIndex, int topicIndex);
};

#endif // THEORYBASE_H
