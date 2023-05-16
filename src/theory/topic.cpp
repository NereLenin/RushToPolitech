#include "topic.h"


const QString &Topic::getFullText() const
{
    return fullText;
}

const QList<TheoryImgInfo> &Topic::getImages() const
{
    return images;
}

const QList<TheoryTicketAnswerInfo> &Topic::getTicketAnswers() const
{
    return ticketAnswers;
}

Topic &Topic::operator =(const Topic &topic)
{
   this->setParent(topic.parent());

    //operator = ?
    this->subjectIndex = topic.subjectIndex;
    this->index = topic.index;

    this->name = topic.name;
    this->fullText = topic.fullText;
    this->images = topic.images;
    this->ticketAnswers = topic.ticketAnswers;

    return *this;
}

int Topic::getSubjectIndex() const
{
    return subjectIndex;
}

QList<TopicPart> Topic::splitTopicOnParts(int textSizeOfOnePart)
{
    QList<TopicPart> splitedTopic;

    int startPartTextIndexInMainText = 0;

    QString mainText = this->fullText;

    while(startPartTextIndexInMainText < mainText.length())
    {
        TopicPart newPart;
        newPart.subjectIndex = subjectIndex;
        newPart.index = index;
        newPart.name = name;

        //находим подстроку с обрезкой по слову, делаем кусок
        newPart.text = subStringWithWordWrap(mainText,startPartTextIndexInMainText,textSizeOfOnePart);
        int endPartTextIndexInMainText = startPartTextIndexInMainText + newPart.text.length();

        //заполняем изображения для нее
        newPart.img = findImgInTextPart(startPartTextIndexInMainText, endPartTextIndexInMainText);

        //ищем ответ на билет с корректировкой индексов
        newPart.answer = getTicketInTextPart(startPartTextIndexInMainText, endPartTextIndexInMainText);

        //добавляем в наш лист
        splitedTopic.append(newPart);

        //идем на след кусок
        startPartTextIndexInMainText = endPartTextIndexInMainText;
    }

    return splitedTopic;
}

int Topic::getIndex(){
    return index;
}

QString Topic::getName(){
    return name;
}

Topic::Topic(QObject *parent) : QObject{parent}
{
    subjectIndex = 0;
    index = 0;
}

Topic::Topic(const Topic &topic): QObject{topic.parent()}
{
    this->subjectIndex = topic.subjectIndex;
    this->index = topic.index;
    this->name = topic.name;
    this->fullText = topic.fullText;
    this->images = topic.images;
    this->ticketAnswers = topic.ticketAnswers;
}

int TopicPart::getIndex() const
{
    return index;
}

const QString &TopicPart::getName() const
{
    return name;
}

const QString &TopicPart::getText() const
{
    return text;
}

const QString &TopicPart::getImg() const
{
    return img;
}

const TheoryTicketAnswerInfo &TopicPart::getAnswer() const
{
    return answer;
}

TopicPart &TopicPart::operator=(const TopicPart &topicPart)
{
    this->subjectIndex = topicPart.subjectIndex;
    this->index = topicPart.index;
    this->name = topicPart.name;
    this->text = topicPart.text;
    this->img = topicPart.img;
    this->answer = topicPart.answer;

    return *this;
}

QString Topic::subStringWithWordWrap(QString text, int subStrStart, int subStrSize){
    if(subStrStart+subStrSize >= text.length())//если размер подстроки указан так, что подразумевает выход за строку, делаем размер по конец текста
        subStrSize = text.length()-subStrStart;

    int wordWrapSubSize = subStrSize;

    //расширяем строку до конца слова
    for(;subStrStart+wordWrapSubSize < text.length() && (text[subStrStart+wordWrapSubSize] != '\n' && text[subStrStart+wordWrapSubSize] != ' '); wordWrapSubSize++);

    return text.mid(subStrStart,wordWrapSubSize);
}

QString Topic::findImgInTextPart(int startPart, int endPart){

    for(int i=0;i<images.size();i++){
        if(isTextPositionInTextPart(images[i].getPositionInText(), startPart, endPart))
            return images[i].getImageUrl();
    }
    return "";
}

TheoryTicketAnswerInfo Topic::getTicketInTextPart(int startPart, int endPart)
{
    int currentTicketAnswerStart = 0;
    int currentTicketAnswerEnd = 0;
    int currentTicketIndex = 0;

    int indexOfStartAnswerInTextPart = 0;
    int indexOfEndAnswerInTextPart = 0;

    bool isThisAnswerInOurTextPart = false;

    for(int i=0;i< ticketAnswers.size();i++){
        currentTicketAnswerStart = ticketAnswers[i].getIndexOfStartAnswerInText();
        currentTicketAnswerEnd = ticketAnswers[i].getIndexOfEndAnswerInText();
        currentTicketIndex = ticketAnswers[i].getTicketIndex();

        indexOfStartAnswerInTextPart = 0;
        indexOfEndAnswerInTextPart = 0;

        //если в отрывке и начало и конец
        if(isTextPositionInTextPart(currentTicketAnswerStart, startPart, endPart) &&
                isTextPositionInTextPart(currentTicketAnswerEnd, startPart, endPart))
        {
            //переводим номер из глобального, в номер в куске текста, вычитая координату начала
            indexOfStartAnswerInTextPart = currentTicketAnswerStart - startPart;
            indexOfEndAnswerInTextPart = currentTicketAnswerEnd - startPart;

        }else
            if(currentTicketAnswerStart <= startPart && currentTicketAnswerEnd >= endPart)
            {//если кусок целиком внутри выделения, но и начало и конец в других блоках
                indexOfStartAnswerInTextPart = 0;
                indexOfEndAnswerInTextPart = endPart - startPart;//подчеркиваем до конца куска текста
            }
            else
                if(isTextPositionInTextPart(currentTicketAnswerStart, startPart, endPart))//если в куске начало, а конец в каком то следующем
                {
                    indexOfStartAnswerInTextPart = currentTicketAnswerStart - startPart;
                    indexOfEndAnswerInTextPart = endPart - startPart;//подчеркиваем до конца куска текста

                }else
                    if(isTextPositionInTextPart(currentTicketAnswerEnd, startPart, endPart))//если в куске только конец
                    {
                        indexOfStartAnswerInTextPart = 0;//подчеркиваем от самого начала
                        indexOfEndAnswerInTextPart = currentTicketAnswerEnd - startPart;
                    }

        isThisAnswerInOurTextPart = (indexOfStartAnswerInTextPart != 0) || (indexOfEndAnswerInTextPart != 0);

        if(isThisAnswerInOurTextPart)
        {
            TheoryTicketAnswerInfo currentAnswerInTextPart(currentTicketIndex,indexOfStartAnswerInTextPart, indexOfEndAnswerInTextPart);
            return currentAnswerInTextPart;
        }

    }

    TheoryTicketAnswerInfo emptyTicketInfo;
    return emptyTicketInfo;
}

bool Topic::isTextPositionInTextPart(int positionInText, int startOfTextPart, int endOfTextPart)
{
    return (positionInText >= startOfTextPart) && (positionInText <= endOfTextPart);
}

TopicPart::TopicPart(QObject *parent) : QObject{parent}
{
    subjectIndex = 0;
    index = 0;
}

TopicPart::TopicPart(const TopicPart &topicPart): QObject{topicPart.parent()}
{
    this->subjectIndex = topicPart.subjectIndex;
    this->index = topicPart.index;
    this->name = topicPart.name;
    this->text = topicPart.text;
    this->img = topicPart.img;
    this->answer = topicPart.answer;

}

int TopicPart::getSubjectIndex() const
{
    return subjectIndex;
}
