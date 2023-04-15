#include "exclamations.h"

QList<QString> jsonArrayToListString(QJsonArray jsonListOfStrings){
    QList<QString> returnList;

    for(int i=0;i < jsonListOfStrings.size();i++)
        returnList.append(jsonListOfStrings[i].toObject().value("text").toString());

    return returnList;
}

void Exclamations::printList(QList<QString> list)
{
    for(int i=0;i<list.size();i++)
        qDebug() << "   " << list[i];
}

Exclamations::~Exclamations()
{
    if(randomGenerator != nullptr)
    {
        //delete randomGenerator;
        randomGenerator = nullptr;
    }
}

void Exclamations::readExclamationsFromTheBase(QString pathToBase)
{
    //нада ли если читается дальше файлом и если шо ошибка буит там
    if(pathToBase == "" ) // \\ проверка на существование файла в qrc
    {
        //исключение путь нулевой до ебучей базы
        qDebug() << "Пустой путь до базы";
        return;
    }

    QFile exclamationsJSONfile(pathToBase);

    if(!exclamationsJSONfile.open( QIODevice::ReadOnly ))
    {
        //исключение нет файла с базой
        qDebug() << "не читается файл ебать";
        return;
    }

    QJsonParseError error;
    QJsonDocument exclamationsDocument = QJsonDocument::fromJson(exclamationsJSONfile.readAll(),&error);
    exclamationsJSONfile.close();

    if(error.error != QJsonParseError::NoError)
            {
                //исключение не парсится файл с базой
                qDebug() << "Ошибка чтения БД для восклицаний";
                qDebug() << error.errorString();
                return;
            }

    //read end
    QJsonObject examExclamationsJson = exclamationsDocument.object().value("forExam").toObject();
    QJsonObject otherExclamationsJson = exclamationsDocument.object().value("forAnyOtherLearning").toObject();

    double version = exclamationsDocument.object().value("version").toDouble();

    if(examExclamationsJson.isEmpty() || otherExclamationsJson.isEmpty())
    {
        qDebug() << "Ошибка парса восклицаний";
        return;
    }

    QJsonArray examGood = examExclamationsJson.value("goodTextes").toArray();
    QJsonArray examBad = examExclamationsJson.value("badTextes").toArray();

    QJsonArray otherGood = otherExclamationsJson.value("goodTextes").toArray();
    QJsonArray otherBad = otherExclamationsJson.value("badTextes").toArray();

    goodExamExclamations = jsonArrayToListString(examGood);
    badExamExclamations = jsonArrayToListString(examBad);

    goodLearnExclamations = jsonArrayToListString(otherGood);
    badLearnExclamations = jsonArrayToListString(otherBad);

    qDebug() << "Loaded" << goodExamExclamations.size()+badExamExclamations.size()+goodLearnExclamations.size()+badLearnExclamations.size() <<
    "exclamations, baseName|version:" <<  exclamationsDocument.object().value("name").toString() << "|" << version ;

}

int Exclamations::getRandomNumber(int min, int max)
{
    return random::randomNumber(min,max);
}

Exclamations::Exclamations(QString pathToBase)
{
    randomGenerator = QRandomGenerator::global();
    readExclamationsFromTheBase(pathToBase);
}

QString Exclamations::getOne(Mood mood, TypeLearning forSession)
{
    if(forSession == TypeLearning::Exam)
    {
        if(mood == Mood::Good)
        {
            return goodExamExclamations[getRandomNumber(0,goodExamExclamations.size()-1)];
        }
        else//Mood:Bad
        {
            return badExamExclamations[getRandomNumber(0,badExamExclamations.size()-1)];
        }
    }else
    {
        if(mood == Mood::Good)
        {
            return goodLearnExclamations[getRandomNumber(0,goodLearnExclamations.size()-1)];
        }
        else//Mood:Bad
        {
            return badLearnExclamations[getRandomNumber(0,badLearnExclamations.size()-1)];
        }
    }
}

void Exclamations::debugPrint()
{
    qDebug() << "debug Start";
    qDebug() << "goodExamExclamations:";
    printList(goodExamExclamations);

    qDebug() << "badExamExclamations:";
    printList(badExamExclamations);

    qDebug() << "goodLearnExclamations:";
    printList(goodLearnExclamations);

    qDebug() << "badLearnExclamations:";
    printList(badLearnExclamations);

}
