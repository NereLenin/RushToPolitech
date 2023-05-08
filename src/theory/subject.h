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
public:
    explicit Subject(QObject *parent = nullptr);
    Subject(const Subject& subj);

    int index;
    QString name;
    QString iconUrl;

    QList <Topic> topics;

    const QString &getName() const;
    int getIndex() const;

    const QList<Topic> &getTopics() const;
    const QString &getIconUrl() const;

    Subject& operator=(const Subject& subj);
};

#endif // SUBJECT_H
