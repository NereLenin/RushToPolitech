#ifndef TOPIC_H
#define TOPIC_H
#include <QObject>
#include <QList>
#include "theoryimginfo.h"
#include "theoryticketinfo.h"

class TopicPart;

class Topic : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int topicIndex READ getIndex CONSTANT)
    Q_PROPERTY(int subjIndex READ getSubjectIndex CONSTANT)
    Q_PROPERTY(QString topicName READ getName CONSTANT)
    Q_PROPERTY(QString fullText READ getFullText CONSTANT)

private:
     QString subStringWithWordWrap(QString text, int subStrStart, int subStrSize);

     QString findImgInTextPart(int startPart,int endPart);

     TheoryTicketAnswerInfo getTicketInTextPart(int startPart,int endPart);

     bool isTextPositionInTextPart(int positionInText, int startOfTextPart, int endOfTextPart);
public:
    int subjectIndex;
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
    int getSubjectIndex() const;

    QList<TopicPart> splitTopicOnParts(int textSizeOfOnePart = 20);
};

class TopicPart : public QObject
{
private:
    int subjectIndex;
    int index;
    QString name;

    QString text;
    QString img;
    TheoryTicketAnswerInfo answer;


public:
    explicit TopicPart(QObject *parent = nullptr);
    TopicPart(const TopicPart& topicPart);

    int getSubjectIndex() const;
    int getIndex() const;

    const QString &getName() const;
    const QString &getText() const;
    const QString &getImg() const;
    const TheoryTicketAnswerInfo &getAnswer() const;

    void debugPrint(){
        qDebug() << "subjInd" << subjectIndex << "ind" << index << "name" << name;
        qDebug() << " textPart" << text;
        qDebug() << " img " << img;
        qDebug() << " answer tInd" << answer.getTicketIndex() << " b:" << answer.getIndexOfStartAnswerInText() << "e:" << answer.getIndexOfEndAnswerInText();
    }

    TopicPart& operator=(const TopicPart& topicPart);

    friend class Topic;
};

#endif // TOPIC_H
