#include "subtopic.h"

QString Subtopic::subStringWithWordWrap(QString text, int subStrStart, int subStrSize)
{
    if(subStrStart+subStrSize >= text.length())//если размер подстроки указан так, что подразумевает выход за строку, делаем размер по конец текста
        subStrSize = text.length()-subStrStart;

    int wordWrapSubSize = subStrSize;

    //расширяем строку до конца слова
    for(;subStrStart+wordWrapSubSize < text.length() && (text[subStrStart+wordWrapSubSize] != '\n' && text[subStrStart+wordWrapSubSize] != ' '); wordWrapSubSize++);

    return text.mid(subStrStart,wordWrapSubSize);
}

QString Subtopic::findImgInTextPart(int startPart, int endPart)
{
    for(int i=0;i<images.size();i++){
        if(isTextPositionInTextPart(images[i].getPositionInText(), startPart, endPart))
            return images[i].getImageUrl();
    }
    return "";
}

TheoryTicketAnswerInfo Subtopic::getTicketInTextPart(int startPart, int endPart)
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

bool Subtopic::isTextPositionInTextPart(int positionInText, int startOfTextPart, int endOfTextPart)
{
 return (positionInText >= startOfTextPart) && (positionInText <= endOfTextPart);
}

Subtopic::Subtopic(QObject *parent)
    : QObject{parent}
{
    subjectIndex = 0;
    topicIndex = 0;
    index = 0;
}

Subtopic::Subtopic(const Subtopic &subtopic) : QObject{subtopic.parent()}
{
    this->subjectIndex = subtopic.subjectIndex;
    this->topicIndex = subtopic.topicIndex;
    this->index = subtopic.index;
    this->name = subtopic.name;
    this->fullText = subtopic.fullText;
    this->images = subtopic.images;
    this->ticketAnswers = subtopic.ticketAnswers;
}

int Subtopic::getIndex() const{
    return index;
}

int Subtopic::getSubjectIndex() const{
    return subjectIndex;
}

int Subtopic::getTopicIndex() const{
    return topicIndex;
}

const QString &Subtopic::getName() const{
    return name;
}

const QString &Subtopic::getFullText() const{
    return fullText;
}

const QList<TheoryImgInfo> &Subtopic::getImages() const{
    return images;
}

const QList<TheoryTicketAnswerInfo> &Subtopic::getTicketAnswers() const{
    return ticketAnswers;
}

QList<SubtopicPart> Subtopic::splitSubtopicOnParts(int textSizeOfOnePart)
{
    QList<SubtopicPart> splitedTopic;

    int startPartTextIndexInMainText = 0;

    QString mainText = this->fullText;

    while(startPartTextIndexInMainText < mainText.length())
    {
        SubtopicPart newPart;
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

Subtopic &Subtopic::operator=(const Subtopic &subtopic){

    this->subjectIndex = subtopic.subjectIndex;
    this->topicIndex = subtopic.topicIndex;
    this->index = subtopic.index;
    this->name = subtopic.name;
    this->fullText = subtopic.fullText;
    this->images = subtopic.images;
    this->ticketAnswers = subtopic.ticketAnswers;

    return *this;
}
