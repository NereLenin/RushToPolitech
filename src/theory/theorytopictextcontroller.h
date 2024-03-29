#ifndef THEORYTOPICTEXTCONTROLLER_H
#define THEORYTOPICTEXTCONTROLLER_H

#include <QObject>
#include "topic.h"

class TheorySubtopicTextController : public QObject
{
    Q_OBJECT
    // в appEnine
    //сигнал readTheory(subjindex, topicindex) просто теорию

    //сигнал readTheoryForTicket(ticketIndex)

    //нижняя менюха в трех состояниях - firstPage, midle, last
    //состояние пляшет от свойств countOfPages, currentPageNumber

    //одна страничка, текст в нее берется из свойства, обновляющегося по событию pageChanged
    //Изначально текст list[0], при /back nextpage параметры из TopicPart пиздошутся в свойства, свойства обновляются
    //если тикетхайлайт не 0, ищем в топик партах отмеченый билет, если есть такой

    //property

private:
    QList<SubtopicPart> subtopicParts;
    int subjIndex;
    int topicIndex;
    QString name;

    QString mainText;

    QString imageUrl;

    int currentHighlightStart;
    int currentHighlighEnd;
    int indexHighlitedTicket;

    int currentPage;

public:
    explicit TheorySubtopicTextController(QObject *parent = nullptr);

    int countOfPages();

    void setSubtopic(Subtopic &subtopic, int textPerPage = 20);

    void showPage(int pageIndex = 0);
    void showAnswerTicket(int ticketIndex);

    void nextPage();
    void previousPage();
    void setHighlightAnswerForTicket(int newHighlightAnswerForTicket);

public:

    const QString &getName() const;
    const QString &getMainText() const;
    const QString &getImageUrl() const;

    int getCurrentHighlightStart() const;
    int getCurrentHighlighEnd() const;

    int getCurrentPage() const;

    int getSubjIndex() const;

    int getTopicIndex() const;

signals:
    void pageChanged();

};

#endif // THEORYTOPICTEXTCONTROLLER_H
