#include "ticketstatisticdatabasedriver.h"

TicketStatisticDataBaseDriver::TicketStatisticDataBaseDriver()
{

}

void TicketStatisticDataBaseDriver::saveStatisticInBase(TicketsStatisticService &from, QString pathToBaseInto)
{
    QJsonDocument statisticJsonDocument = statisticBaseToJsonDoc(from);
    writeStatisticJsonDocIntoFile(statisticJsonDocument,pathToBaseInto);
}

void TicketStatisticDataBaseDriver::loadStatisticBase(QString pathToBaseFrom, TicketsStatisticService &into)
{
    QJsonDocument statisticJsonDocument = loadStatisticJsonDocFromFile(pathToBaseFrom);
    parseStatisticJsonDoc(statisticJsonDocument,into);
}


QJsonDocument TicketStatisticDataBaseDriver::statisticBaseToJsonDoc(TicketsStatisticService &statisticBase)
{
    QJsonArray listOfStatistic;

    //заполняем Json массив нашими данными о билетах
    //заменить на foreach
    for(int i=0;i < statisticBase.ticketStatisticBase.size(); i++ )
        listOfStatistic.append(statisticBase.ticketStatisticBase[i].toJson());

    //помечаем что это наша база
    QJsonObject base;
    base["name"] = "statisticBase";
    base["ticketStatistic"] = listOfStatistic;
    base["bonusToPassExam"] = statisticBase.dayBonusToChanceToPassExam;
    base["writeBonusDate"] = QDate::currentDate().toJulianDay();

    //формируем документ
    QJsonDocument doc(base);
    return doc;
}

void TicketStatisticDataBaseDriver::writeStatisticJsonDocIntoFile(QJsonDocument &baseJsonDocument, QString pathToBase)
{
    QFile fileJson(pathToBase); //тут я записываю файл в текущей директории

    bool isFileOpened = fileJson.open(QIODevice::WriteOnly);

    if(!isFileOpened)//все верно, если файла нет, он будет создан
   {
        qDebug() << "ошибка записи базы в файл";
        return;
        //исключение
   }
    fileJson.write(baseJsonDocument.toJson());
    fileJson.close();
}

QJsonDocument TicketStatisticDataBaseDriver::loadStatisticJsonDocFromFile(QString pathToBaseFrom)
{
    QFile statisticJSONfile(pathToBaseFrom);

    if(!statisticJSONfile.open( QIODevice::ReadOnly ))
    {
        //исключение нет файла с базой
        qDebug() << "not chitaetsa fayl so statistikoi ebat";
        return *(new QJsonDocument());
    }

    QJsonParseError error;
    QJsonDocument statisticJsonDocument = QJsonDocument::fromJson(statisticJSONfile.readAll(),&error);
    statisticJSONfile.close();

    if(error.error != QJsonParseError::NoError)
            {
                //исключение не парсится файл с базой
                qDebug() << "Ошибка чтения БД";
                qDebug() << error.errorString();

            }
    return statisticJsonDocument;
}

void TicketStatisticDataBaseDriver::parseStatisticJsonDoc(QJsonDocument statisticJsonDocFrom, TicketsStatisticService &into)
{
    QDate dateOfBonusWritedInBase;
    dateOfBonusWritedInBase = QDate::fromJulianDay(statisticJsonDocFrom.object().value("writeBonusDate").toInt());

    if(dateOfBonusWritedInBase == QDate::currentDate())//если записанный дневной бонус за сегодня
        into.setDayBonusToChanceToPassExam(statisticJsonDocFrom.object().value("bonusToPassExam").toInt());
    else
        into.setRandomDayBonusToChanceToPassExam();
    //читаем массив билетов
    QJsonArray jsonStatistic = statisticJsonDocFrom.object().value("ticketStatistic").toArray();

    //сначала проверить пустой ли файл, если есть че читать тогда чистим
    into.ticketStatisticBase.clear();

    QJsonObject jsonTicketInfo;

    for(int i = 0; i < jsonStatistic.size(); i++)
    {

        jsonTicketInfo = jsonStatistic[i].toObject();

        into.ticketStatisticBase.append(*TicketInfo::createTicketInfo(jsonTicketInfo));

    }

    qDebug() << "Loaded" << into.ticketStatisticBase.size() << "infoTickets, baseName: " << statisticJsonDocFrom.object().value("name").toString();
}
