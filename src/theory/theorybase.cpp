#include "theorybase.h"

TheoryBase::TheoryBase(QString pathToJsonDB){
    TheoryBaseReader::readTheoryFromJsonDB(subjects, pathToJsonDB);
}
void TheoryBase::clear()
{
    subjects.clear();
}

Subject TheoryBase::getSubject(int index)
{

    if(index >= 0 && index < subjects.size())
    {
        return subjects[index];
    }

    Subject nullSbj;
    return nullSbj;
}

Topic TheoryBase::getTopic(int subjectIndex, int topicIndex)
{
    Subject neededSubject = getSubject(subjectIndex);

    if(topicIndex >= 0 && topicIndex < neededSubject.topics.size())
    {
        return neededSubject.topics[topicIndex];
    }

    Topic nullTopic;
    return nullTopic;
}
