#ifndef THEORYBASE_H
#define THEORYBASE_H
#include "subject.h"
#include "theorybasereader.h"
#include <QMap>

class TheoryBase
{
private:
    QList <Subject> subjects;
    QMap <int,Topic*> topicsForTickets;
    QMap <int,Topic*> readTopicsForTickets();
public:
    TheoryBase(QString pathToJsonDB = ":/ticketBase/TheoryBase.json");
    void clear();

    const QList <Subject>& getSubjects();
    Subject* getSubject(int index);

    Topic* getTopic(int subjectIndex, int topicIndex);
    Topic* getTopicForTicket(int ticketIndex);

    ~TheoryBase(){
        qDebug() << "Деструктор для базы теории";
    }
};

#endif // THEORYBASE_H
