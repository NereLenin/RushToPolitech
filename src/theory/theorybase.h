#ifndef THEORYBASE_H
#define THEORYBASE_H
#include <QMap>

#include "subject.h"
#include "theorybasereader.h"
#include "theorytopictextcontroller.h"


class TheoryBase
{
private:
    QList <Subject> subjects;
    QMap <int,Topic*> topicsForTickets;
    QMap <int,Topic*> readTopicsForTickets();
public:

    TheoryBase(QString pathToJsonDB = ":/ticketBase/TheoryBase.json");
    void clear();

    TheoryTopicTextController topicController;

    const QList <Subject>& getSubjects();
    Subject* getSubject(int index);

    Topic* getTopic(int subjectIndex, int topicIndex);
    Topic* getTopicForTicket(int ticketIndex);

    TheoryTopicTextController& getTopicController(Topic &topic, int sizeOfOnePage = 20);

    ~TheoryBase(){
        qDebug() << "Деструктор для базы теории";
    }
};

#endif // THEORYBASE_H
