#ifndef EXCLAMATIONS_H
#define EXCLAMATIONS_H
#include "src/learnsession.h"

#include <QString>
#include <QList>
#include <QFile>

#include <QJsonParseError>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

enum Mood{Bad,Good};

class Exclamations
{
private:
    QRandomGenerator *randomGenerator;

    QList <QString> goodExamExclamations;
    QList <QString> badExamExclamations;

    QList <QString> goodLearnExclamations;
    QList <QString> badLearnExclamations;

    void readExclamationsFromTheBase(QString pathToBase);
    int getRandomNumber(int min, int max);

public:
    Exclamations(QString pathToBase = ":/ticketBase/ExclamationsBase.json");

    QString getOne(Mood mood = Mood::Good, LearnSession::TypeLearning forSession = LearnSession::DefaultLearning);

    void debugPrint();

    void printList(QList<QString> list);

    ~Exclamations();
};

#endif // EXCLAMATIONS_H
