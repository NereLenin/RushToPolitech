#include "theorybasereader.h"

TheoryBaseReader::TheoryBaseReader()
{

}

QList<TheoryImgInfo> TheoryBaseReader::parseImgTagsInText(QString &text)
{
    QRegularExpression imgTagRegular("<?.img[^<>]+>");
    QRegularExpressionMatch tagMatch = imgTagRegular.match(text);

    QList<TheoryImgInfo> imgList;

    if(tagMatch.hasMatch())
    {

        while(tagMatch.hasMatch())
        {
          TheoryImgInfo newImg(tagMatch.captured(0),tagMatch.capturedStart(0));
          imgList.append(newImg);
          text = text.remove(tagMatch.capturedStart(0),tagMatch.capturedLength(0));//удаляем тэг из текста
          tagMatch = imgTagRegular.match(text);//ищем дальше
        }
    }
    return imgList;
}

QList<TheoryTicketAnswerInfo> TheoryBaseReader::parseTicketsAnswerInText(QString &text)
{
    QRegularExpression answerOpenTagRegular("<?.begin answer for?.[^<>]+>");
    QRegularExpression answerCloseTagRegular("<?./?.end[^<>]+?.>");

    QRegularExpressionMatch matchOpenTag = answerOpenTagRegular.match(text);
    QRegularExpressionMatch matchCloseTag = answerCloseTagRegular.match(text);

    QList <int> openIndex;//вместо листов можно массивы по lastCapturedIndex();
    QList <int> closeIndex;
    QList <int> tickets;

    QList <TheoryTicketAnswerInfo> ticketAnswers;

    if(matchOpenTag.hasMatch() && matchCloseTag.hasMatch())
    {

    //обрабатываем открывающиеся тэги

    QString ticketIndex;
    QRegularExpression notNumbers("[^\\d]+");

        while(matchOpenTag.hasMatch())
        {
          ticketIndex = ((matchOpenTag.captured(0)).remove(notNumbers) );
          tickets.append(ticketIndex.toInt());
          openIndex.append(matchOpenTag.capturedStart(0));

          text = text.remove(matchOpenTag.capturedStart(0),matchOpenTag.capturedLength(0));//удаляем тэг из текста
          matchOpenTag = answerOpenTagRegular.match(text);//ищем дальше
        }

    //закрывающиеся
        matchCloseTag = answerCloseTagRegular.match(text);
        while(matchCloseTag.hasMatch())
        {
          closeIndex.append(matchCloseTag.capturedStart(0));
          text = text.remove(matchCloseTag.capturedStart(0),matchCloseTag.capturedLength(0));//удаляем тэг из текста
          matchCloseTag = answerCloseTagRegular.match(text);//ищем дальше
        }

     int countOfOpen = openIndex.size();
     int countOfClose = closeIndex.size();

    if(countOfOpen > countOfClose){
        qDebug() << "Ошибка парса выделения ответа билета topic:  лишний begin";
        return ticketAnswers;
    } else if(countOfOpen < countOfClose){
        qDebug() << "Ошибка парса выделения ответа билета topic: лишний end";
        return ticketAnswers;
    }


    for(int i=0; i < countOfOpen;i++){
        TheoryTicketAnswerInfo newTicketAnswerInfo(tickets[i],openIndex[i],closeIndex[i]);
        ticketAnswers.append(newTicketAnswerInfo);
    }

    }//has match
    return ticketAnswers;
}

void TheoryBaseReader::readTheoryFromJsonDB(QList<Subject> &subjects, QString pathToJsonDB)
{

    QFile theoryJSONfile(pathToJsonDB);

    if(!theoryJSONfile.open( QIODevice::ReadOnly ))
    {
        //исключение нет файла с базой
        qDebug() << "не читается файл ебать";
        return;
    }

    QJsonParseError error;
    QJsonDocument theoryDocument = QJsonDocument::fromJson(theoryJSONfile.readAll(),&error);
    theoryJSONfile.close();

    if(error.error != QJsonParseError::NoError)
            {
                //исключение не парсится файл с базой
                qDebug() << "Ошибка чтения БД";
                qDebug() << error.errorString();
                return;
            }
    //read end
    QJsonArray jsonSubjects = theoryDocument.object().value("subjects").toArray();
    double version = theoryDocument.object().value("version").toDouble();

    QJsonObject jsonSubject;
    for(int i = 0; i < jsonSubjects.size(); i++)//идем по списку предметов
    {
        jsonSubject = jsonSubjects[i].toObject();

        if(jsonSubject.isEmpty())
        {
            qDebug() << "ошибка парса на" << i;
            return;
        }

        Subject newSubject;
        newSubject.index = jsonSubject.value("subjectIndex").toInt();
        newSubject.name = jsonSubject.value("name").toString();

        QJsonArray jsonSubjectTopics = jsonSubject.value("topics").toArray();
        QJsonObject jsonTopic;

        for(int i=0;i<jsonSubjectTopics.size();i++){//шелестим по темам предмета
           jsonTopic = jsonSubjectTopics[i].toObject();
           Topic newTopic;
           newTopic.index = jsonTopic.value("topicIndex").toInt();
           newTopic.name = jsonTopic.value("name").toString();
           newTopic.fullText = jsonTopic.value("text").toString();

           newTopic.images = parseImgTagsInText(newTopic.fullText);
           newTopic.ticketAnswers = parseTicketsAnswerInText(newTopic.fullText);

           newSubject.topics.append(newTopic);//добавляем тему в предмет
        }

        subjects.append(newSubject);
    }
    qDebug() << "Количество считаных предметов" << subjects.size();
    qDebug() << "Loaded" << subjects.size() << "subjects, baseName|version:" <<  theoryDocument.object().value("name").toString() << "|" << version ;


  /*  for(int i=0;i<subjects.size();i++)
    {
        qDebug() << "---------------------------------------------";
        qDebug() << "   ind:" << subjects[i].index << subjects[i].name;
        qDebug() << " Количество тем:" << subjects[i].topics.size();
        qDebug() << " Темы:";
        for(int j=0;j<subjects[i].topics.size();j++)
        {
         qDebug() << "  -" << subjects[i].topics[j].index << subjects[i].topics[j].name ;
         qDebug() << "  Таблица изображений:";
         for(int k = 0; k < subjects[i].topics[j].images.size(); k++)
         {
             qDebug() << "  -" << subjects[i].topics[j].images[k].getImageUrl() << subjects[i].topics[j].images[k].getPositionInText();
         }
         qDebug() << "  Таблица ответов:";
         for(int k = 0; k < subjects[i].topics[j].ticketAnswers.size(); k++)
         {
             qDebug() << "  - index:" << subjects[i].topics[j].ticketAnswers[k].ticketIndex << "s:" << subjects[i].topics[j].ticketAnswers[k].getIndexOfStartAnswerInText() << "e:"<< subjects[i].topics[j].ticketAnswers[k].getIndexOfEndAnswerInText();
         }
        }


    }

    qDebug() << subjects[0].topics[2].fullText;
    */
}
