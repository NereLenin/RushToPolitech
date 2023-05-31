#include "theorytopictextcontroller.h"


void TheorySubtopicTextController::showPage(int pageIndex){
    if(pageIndex == 0) pageIndex = currentPage;

    if(pageIndex >=0 && pageIndex < countOfPages())
    {
        currentPage = pageIndex;

        name = subtopicParts[currentPage].getName();
        mainText = subtopicParts[currentPage].getText();
        imageUrl = subtopicParts[currentPage].getImg();

        //если на этой странице есть ответ на вопрос, который нужно подсвечивать
        if(indexHighlitedTicket == subtopicParts[currentPage].getAnswer().getTicketIndex())
        {

            currentHighlightStart = subtopicParts[currentPage].getAnswer().getIndexOfStartAnswerInText();
            currentHighlighEnd = subtopicParts[currentPage].getAnswer().getIndexOfEndAnswerInText();

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

void TheorySubtopicTextController::showAnswerTicket(int ticketIndex)//подсветить тикет и включить сразу его начало
{
    if(ticketIndex == 0) return;

    indexHighlitedTicket = ticketIndex;



    for(int i=0;i < subtopicParts.size();i++)
    {
        if(subtopicParts[i].getAnswer().getTicketIndex() == ticketIndex)
        {
            showPage(i);
            break;
        }
    }
}

int TheorySubtopicTextController::countOfPages(){
    return subtopicParts.size();
}

void TheorySubtopicTextController::setSubtopic(Subtopic &subtopic, int textPerPage){

    indexHighlitedTicket = currentHighlighEnd = currentHighlightStart = 0;

    subjIndex = subtopic.getSubjectIndex();
    topicIndex = subtopic.getIndex();

    subtopicParts = subtopic.splitSubtopicOnParts(textPerPage);
    currentPage = 0;
    showPage(currentPage);
}

void TheorySubtopicTextController::nextPage(){
    if(currentPage < countOfPages()-1)
        showPage(++currentPage);
}

void TheorySubtopicTextController::previousPage(){
    if(currentPage > 0)
        showPage(--currentPage);

}

const QString &TheorySubtopicTextController::getName() const
{
    return name;
}

const QString &TheorySubtopicTextController::getMainText() const
{
    return mainText;
}

const QString &TheorySubtopicTextController::getImageUrl() const
{
    return imageUrl;
}

int TheorySubtopicTextController::getCurrentHighlightStart() const
{
    return currentHighlightStart;
}

int TheorySubtopicTextController::getCurrentHighlighEnd() const
{
    return currentHighlighEnd;
}

int TheorySubtopicTextController::getCurrentPage() const
{
    return currentPage+1;
}

int TheorySubtopicTextController::getSubjIndex() const
{
    return subjIndex;
}

int TheorySubtopicTextController::getTopicIndex() const
{
    return topicIndex;
}

TheorySubtopicTextController::TheorySubtopicTextController(QObject *parent) : QObject(parent){
    subjIndex = 0;
    topicIndex = 0;

    currentHighlightStart = 0;
    currentHighlighEnd = 0;

    currentPage = 0;
}

void TheorySubtopicTextController::setHighlightAnswerForTicket(int newHighlightAnswerForTicket)
{
    indexHighlitedTicket = newHighlightAnswerForTicket;
}
