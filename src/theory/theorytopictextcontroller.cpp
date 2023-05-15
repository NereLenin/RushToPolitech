#include "theorytopictextcontroller.h"


void TheoryTopicTextController::showPage(int pageIndex){
    if(pageIndex == 0) pageIndex = currentPage;

    if(pageIndex >=0 && pageIndex < countOfPages())
    {
        currentPage = pageIndex;

        name = topicParts[currentPage].getName();
        mainText = topicParts[currentPage].getText();
        imageUrl = topicParts[currentPage].getImg();

        //если на этой странице есть ответ на вопрос, который нужно подсвечивать
        if(indexHighlitedTicket == topicParts[currentPage].getAnswer().getTicketIndex())
        {

            currentHighlightStart = topicParts[currentPage].getAnswer().getIndexOfStartAnswerInText();
            currentHighlighEnd = topicParts[currentPage].getAnswer().getIndexOfEndAnswerInText();

        }
        else{
            currentHighlightStart = currentHighlighEnd = 0;
        }
        emit pageChanged();

        //            qDebug() << "            " << currentPage << "/" << countOfPages();
        //            qDebug() << name << "answer" << currentHighlightStart << currentHighlighEnd;
        //            qDebug() << mainText;
    }

}

void TheoryTopicTextController::showAnswerTicket(int ticketIndex)//подсветить тикет и включить сразу его начало
{
    if(ticketIndex == 0) return;

    indexHighlitedTicket = ticketIndex;



    for(int i=0;i < topicParts.size();i++)
    {
        if(topicParts[i].getAnswer().getTicketIndex() == ticketIndex)
        {
            showPage(i);
            break;
        }
    }
}

int TheoryTopicTextController::countOfPages(){
    return topicParts.size();
}

void TheoryTopicTextController::setTopic(Topic &topic, int textPerPage){

    indexHighlitedTicket = currentHighlighEnd = currentHighlightStart = 0;

    subjIndex = topic.getSubjectIndex();
    topicIndex = topic.getIndex();

    topicParts = topic.splitTopicOnParts(textPerPage);
    currentPage = 0;
    showPage(currentPage);
}

void TheoryTopicTextController::nextPage(){
    if(currentPage < countOfPages()-1)
        showPage(++currentPage);
}

void TheoryTopicTextController::previousPage(){
    if(currentPage > 0)
        showPage(--currentPage);

}

const QString &TheoryTopicTextController::getName() const
{
    return name;
}

const QString &TheoryTopicTextController::getMainText() const
{
    return mainText;
}

const QString &TheoryTopicTextController::getImageUrl() const
{
    return imageUrl;
}

int TheoryTopicTextController::getCurrentHighlightStart() const
{
    return currentHighlightStart;
}

int TheoryTopicTextController::getCurrentHighlighEnd() const
{
    return currentHighlighEnd;
}

int TheoryTopicTextController::getCurrentPage() const
{
    return currentPage+1;
}

int TheoryTopicTextController::getSubjIndex() const
{
    return subjIndex;
}

int TheoryTopicTextController::getTopicIndex() const
{
    return topicIndex;
}

TheoryTopicTextController::TheoryTopicTextController(QObject *parent) : QObject(parent){
    subjIndex = 0;
    topicIndex = 0;

    currentHighlightStart = 0;
    currentHighlighEnd = 0;

    currentPage = 0;
}

void TheoryTopicTextController::setHighlightAnswerForTicket(int newHighlightAnswerForTicket)
{
    indexHighlitedTicket = newHighlightAnswerForTicket;
}
