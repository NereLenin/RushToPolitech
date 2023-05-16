#include "theorybase.h"

QMap<int, Topic *> TheoryBase::readTopicsForTickets(){
    QMap <int,Topic*> newtopicsForTickets;
    int ticketIndexForThisTopic = 0;

    Subject* currentSubj;
    Topic* currentTopic;


    for(int currentSubjIndex=0; currentSubjIndex < getSubjects().size(); currentSubjIndex++)//по всем предметам
    {
        currentSubj = getSubject(currentSubjIndex+1);
        if(currentSubj == nullptr)
        {
            qDebug() << "readTopicsForTickets : Попытка получить несуществующий предмет с индексом" << currentSubjIndex;
            return newtopicsForTickets;
        }

        for(int currentTopicIndex = 0; currentTopicIndex < currentSubj->getTopics().size(); currentTopicIndex++)//по всем темам
        {
            currentTopic = getTopic(currentSubjIndex+1,currentTopicIndex+1);

            if(currentTopic == nullptr)
            {
                qDebug() << "readTopicsForTickets : Попытка получить несуществую тему с индексом subj:" << currentSubjIndex << "topic: " << currentTopicIndex;
                return newtopicsForTickets;
            }

            for(int currentAnswerTicketInfoIndex = 0; currentAnswerTicketInfoIndex < currentTopic->getTicketAnswers().size(); currentAnswerTicketInfoIndex++)//по всем ответам на вопросы в них
            {
                //получаем номер билета на ответ на который содержится в этой теме
                ticketIndexForThisTopic = currentTopic->getTicketAnswers()[currentAnswerTicketInfoIndex].getTicketIndex();

                //записываем по номеру билета ссылку на тему
                newtopicsForTickets[ticketIndexForThisTopic] = &(subjects[currentSubjIndex].topics[currentTopicIndex]);
            }
        }
    }

    return newtopicsForTickets;
}

TheoryBase::TheoryBase(QString pathToJsonDB){
    TheoryBaseReader::readTheoryFromJsonDB(subjects, pathToJsonDB);
    topicsForTickets = readTopicsForTickets();
}
void TheoryBase::clear()
{
    subjects.clear();
}

const QList<Subject> &TheoryBase::getSubjects()
{
    return subjects;
}

Subject *TheoryBase::getSubject(int index)
{
//    if(index >= 0 && index < subjects.size())
//    {
//        return &subjects[index];//в листе с 0, в базе с 1
//    }

    if(index > 0 && index <= subjects.size())
    {
        return &subjects[index-1];//в листе с 0, в базе с 1
    }

    return nullptr;
}

Topic *TheoryBase::getTopic(int subjectIndex, int topicIndex)
{

//    if(topicIndex >= 0 && topicIndex < getSubject(subjectIndex)->getTopics().size())
//    {
//        return &(getSubject(subjectIndex)->topics[topicIndex]);//в листе с 0, в базе с 1
//    }

    if(topicIndex > 0 && topicIndex <= (getSubject(subjectIndex)->getTopics().size()) )
    {
        return &(getSubject(subjectIndex)->topics[topicIndex-1]);//в листе с 0, в базе с 1
    }

    return nullptr;
}
Topic *TheoryBase::getTopicForTicket(int ticketIndex)
{
    if(!topicsForTickets.contains(ticketIndex))
    {
      qDebug() << "Не найдена тема для билета с номером " << ticketIndex;
      return nullptr;
    }
    return topicsForTickets[ticketIndex];
}

TheoryTopicTextController &TheoryBase::getTopicController(Topic &topic, int sizeOfOnePage){
    topicController.setTopic(topic,sizeOfOnePage);
    return topicController;
}
