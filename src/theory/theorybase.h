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
    QMap <int,Subtopic*> subtopicsForTickets;
    QMap <int,Subtopic*> readSubtopicsForTickets();
public:

    TheoryBase(QString pathToJsonDB = ":/ticketBase/TheoryBase.json");
    void clear();

    TheorySubtopicTextController subtopicController;

    const QList <Subject>& getSubjects();
    Subject* getSubject(int index);

    Topic* getTopic(int subjectIndex, int topicIndex);
    Subtopic *getSubtopic(int subjectIndex, int topicIndex, int subtopicIndex);
    Subtopic *getSubtopicForTicket(int ticketIndex);

    TheorySubtopicTextController& getTopicController(Subtopic &subtopic, int sizeOfOnePage = 20);

    ~TheoryBase(){
        qDebug() << "Деструктор для базы теории";
    }
};

#endif // THEORYBASE_H
