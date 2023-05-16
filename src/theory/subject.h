#ifndef SUBJECT_H
#define SUBJECT_H

#include <QObject>

#include "topic.h"

class Subject : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int subjectIndex READ getIndex CONSTANT)
    Q_PROPERTY(QString subjName READ getName CONSTANT)
    Q_PROPERTY(QString subjIconUrl READ getIconUrl CONSTANT)
private:
    int index;
    QString name;
    QString iconUrl;
public:
    explicit Subject(QObject *parent = nullptr);
    Subject(const Subject& subj);

    QList <Topic> topics;

    const QString &getName() const;
    int getIndex() const;

    const QList<Topic> &getTopics() const;
    const QString &getIconUrl() const;

    Subject& operator=(const Subject& subj);

    friend class TheoryBaseReader;
};

#endif // SUBJECT_H
