#ifndef SUBTOPIC_H
#define SUBTOPIC_H

#include <QObject>
#include <QList>

#include "theoryimginfo.h"
#include "theoryticketinfo.h"

class SubtopicPart;
class TheoryBaseReader;

class Subtopic : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int subjIndex READ getSubjectIndex CONSTANT)
    Q_PROPERTY(int topicIndex READ getTopicIndex CONSTANT)
    Q_PROPERTY(int subtopicIndex READ getIndex CONSTANT)

    Q_PROPERTY(QString subtopicName READ getName CONSTANT)
    Q_PROPERTY(QString fullText READ getFullText CONSTANT)
public:


private:
    int subjectIndex;
    int topicIndex;
    int index;
    QString name;
    QString fullText;

    QList <TheoryImgInfo> images;
    QList <TheoryTicketAnswerInfo> ticketAnswers;

    //func for split on parts
    QString subStringWithWordWrap(QString text, int subStrStart, int subStrSize);

    QString findImgInTextPart(int startPart,int endPart);

    TheoryTicketAnswerInfo getTicketInTextPart(int startPart,int endPart);

    bool isTextPositionInTextPart(int positionInText, int startOfTextPart, int endOfTextPart);

public:
    explicit Subtopic(QObject *parent = nullptr);
    explicit Subtopic(const Subtopic& subtopic);

    int getIndex() const;
    int getSubjectIndex() const;
    int getTopicIndex() const;

    const QString &getName() const;
    const QString &getFullText() const;

    const QList<TheoryImgInfo> &getImages() const;
    const QList<TheoryTicketAnswerInfo> &getTicketAnswers() const;

    QList<SubtopicPart> splitSubtopicOnParts(int textSizeOfOnePart = 20);

    Subtopic& operator=(const Subtopic& subtopic);

    friend class TheoryBaseReader;

    void debugPrint(){
        qDebug() << "Subtopic " << subjectIndex << topicIndex << index;
        qDebug() << ticketAnswers.size() <<  "answers.";
        qDebug() << images.size() <<  "images.";

    }
signals:

};

class SubtopicPart : public QObject
{
private:
    int subjectIndex;
    int topicIndex;
    int index;
    QString name;

    QString text;
    QString img;
    TheoryTicketAnswerInfo answer;

public:
    explicit SubtopicPart(QObject *parent = nullptr) : QObject{parent}{
       subjectIndex = topicIndex = index = 0;
    }

    SubtopicPart(const SubtopicPart& subtopicPart): QObject{subtopicPart.parent()}{
        subjectIndex = subtopicPart.subjectIndex;
        topicIndex = subtopicPart.topicIndex;
        index = subtopicPart.index;
        name = subtopicPart.name;
        text = subtopicPart.text;
        img = subtopicPart.img;
        answer = subtopicPart.answer;
    }

    int getSubjectIndex() const{
        return subjectIndex;
    }
    int getTopicIndex() const{
        return topicIndex;
    }
    int getIndex() const{
        return index;
    }

    const QString &getName() const{
        return name;
    }
    const QString &getText() const{
        return text;
    }
    const QString &getImg() const{
        return img;
    }
    const TheoryTicketAnswerInfo &getAnswer() const{
        return answer;
    }

    void debugPrint(){
        qDebug() << "subjInd" << subjectIndex << "ind" << index << "name" << name;
        qDebug() << " textPart" << text;
        qDebug() << " img " << img;
        qDebug() << " answer tInd" << answer.getTicketIndex() << " b:" << answer.getIndexOfStartAnswerInText() << "e:" << answer.getIndexOfEndAnswerInText();
    }

    SubtopicPart& operator=(const SubtopicPart& subtopicPart){
        setParent(subtopicPart.parent());
        subjectIndex = subtopicPart.subjectIndex;
        topicIndex = subtopicPart.topicIndex;
        index = subtopicPart.index;
        name = subtopicPart.name;
        text = subtopicPart.text;
        img = subtopicPart.img;
        answer = subtopicPart.answer;

        return *this;
    }

    friend class Subtopic;
};

#endif // SUBTOPIC_H
