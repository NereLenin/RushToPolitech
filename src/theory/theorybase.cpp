#include "theorybase.h"

QMap<int, Subtopic*> TheoryBase::readSubtopicsForTickets(){
    QMap <int,Subtopic*> newtopicsForTickets;

    Subject* currentSubj;
    Topic* currentTopic;
    Subtopic* currentSubtopic;
    TheoryTicketAnswerInfo currentTicket;


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

            for(int currentSubtopicIndex = 0; currentSubtopicIndex < currentTopic->getSubtopics().size(); currentSubtopicIndex++)//по всем ответам на вопросы в них
            {

                currentSubtopic = getSubtopic(currentSubjIndex+1,currentTopicIndex+1,currentSubtopicIndex+1);

                if(currentSubtopic == nullptr)
                {
                    qDebug() << "readTopicsForTickets : Попытка получить несуществую тему с индексом subj:" << currentSubjIndex << "topic: " << currentTopicIndex;
                    return newtopicsForTickets;
                }

                for(int currentAnswerInSubtopic = 0; currentAnswerInSubtopic < currentSubtopic->getTicketAnswers().size();currentAnswerInSubtopic++)
                {
                    //получаем номер билета на ответ на который содержится в этой теме
                    currentTicket = (currentSubtopic->getTicketAnswers()[currentAnswerInSubtopic]);

                    //записываем по номеру билета ссылку на подтему
                    newtopicsForTickets[currentTicket.getTicketIndex()] = (currentSubtopic);
                }



            }
        }
    }

    return newtopicsForTickets;
}

TheoryBase::TheoryBase(QString pathToJsonDB){
    TheoryBaseReader::readTheoryFromJsonDB(subjects, pathToJsonDB);
    subtopicsForTickets = readSubtopicsForTickets();
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

Subtopic *TheoryBase::getSubtopic(int subjectIndex, int topicIndex, int subtopicIndex)
{
    Topic *currentTopic = getTopic(subjectIndex,topicIndex);

    if(currentTopic!=nullptr)
    if(subtopicIndex > 0 && subtopicIndex <= (currentTopic->getSubtopics().size()) )
    {
        return &(currentTopic->getSubtopics()[subtopicIndex-1]);//в листе с 0, в базе с 1
    }

    return nullptr;
}

Subtopic *TheoryBase::getSubtopicForTicket(int ticketIndex)
{
    if(!subtopicsForTickets.contains(ticketIndex))
    {
      qDebug() << "Не найдена тема для билета с номером " << ticketIndex;
      return nullptr;
    }
    return subtopicsForTickets[ticketIndex];
}

TheorySubtopicTextController &TheoryBase::getTopicController(Subtopic &subtopic, int sizeOfOnePage){
    subtopicController.setSubtopic(subtopic,sizeOfOnePage);
    return subtopicController;
}
