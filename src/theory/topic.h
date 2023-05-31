#ifndef TOPIC_H
#define TOPIC_H
#include <QObject>
#include <QList>
#include "theoryimginfo.h"
#include "theoryticketinfo.h"
#include "subtopic.h"

class TheoryBaseReader;

class Topic : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int topicIndex READ getIndex CONSTANT)
    Q_PROPERTY(int subjIndex READ getSubjectIndex CONSTANT)
    Q_PROPERTY(QString topicName READ getName CONSTANT)

private:
    int subjectIndex;
    int index;
    QString name;

    QList <Subtopic> subtopics;
public:
    explicit Topic(QObject *parent = nullptr);
    Topic(const Topic& topic);

    int getSubjectIndex() const;
    int getIndex();

    QString getName();

    QList<Subtopic> &getSubtopics();


    Topic& operator=(const Topic& topic);

    friend class TheoryBaseReader;
};


#endif // TOPIC_H
