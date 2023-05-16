#ifndef THEORYBASEREADER_H
#define THEORYBASEREADER_H
#include <QString>
#include <QList>
#include <QFile>

#include <QJsonParseError>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include <QRegularExpression>

#include "subject.h"

class TheoryBaseReader
{
private:
    TheoryBaseReader();
    static QList <TheoryImgInfo> parseImgTagsInText(QString &text);
    static QList <TheoryTicketAnswerInfo> parseTicketsAnswerInText(QString &text);
public:
    static void readTheoryFromJsonDB(QList <Subject> &subjects, QString pathToJsonDB = ":/ticketBase/TheoryBase.json");
};

#endif // THEORYBASEREADER_H
