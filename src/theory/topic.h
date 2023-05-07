#ifndef TOPIC_H
#define TOPIC_H
#include <QObject>
#include <QList>
#include "theoryimginfo.h"
#include "theoryticketinfo.h"


class Topic : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int topicIndex READ getIndex CONSTANT)
    Q_PROPERTY(QString topicName READ getName CONSTANT)
    Q_PROPERTY(QString fullText READ getFullText CONSTANT)
public:
    int index;
    QString name;
    QString fullText;

    QList <TheoryImgInfo> images;
    QList <TheoryTicketAnswerInfo> ticketAnswers;

    int getIndex();
    QString getName();
    const QString &getFullText() const;

    explicit Topic(QObject *parent = nullptr);
    Topic(const Topic& topic);


    const QList<TheoryImgInfo> &getImages() const;
    const QList<TheoryTicketAnswerInfo> &getTicketAnswers() const;

    Topic& operator=(const Topic& topic);
};

#endif // TOPIC_H
