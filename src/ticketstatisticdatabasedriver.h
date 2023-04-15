#ifndef TICKETSTATISTICDATABASEDRIVER_H
#define TICKETSTATISTICDATABASEDRIVER_H
#include "tickets.h"
#include "ticketinfo.h"
#include <QJsonDocument>
#include <QFile>
#include "src/ticketsstatisticservice.h"

//предварительное обьявление сервиса для которого реализуем чтение запись
class TicketsStatisticService;

class TicketStatisticDataBaseDriver{
private:
    TicketStatisticDataBaseDriver();

    //from statisticBase In App into File useful functions
    static QJsonDocument statisticBaseToJsonDoc(TicketsStatisticService &statisticBase);
    static void writeStatisticJsonDocIntoFile(QJsonDocument &baseJsonDocument, QString pathToBase);

    //from File into statisticBase In App
    static QJsonDocument loadStatisticJsonDocFromFile(QString pathToBaseFrom);
    static void parseStatisticJsonDoc(QJsonDocument statisticJsonDocFrom, TicketsStatisticService& into);

public:
    static void saveStatisticInBase(TicketsStatisticService &from, QString pathToBaseInto);
    static void loadStatisticBase(QString pathToBaseFrom, TicketsStatisticService &into);

  };
#endif // TICKETSTATISTICDATABASEDRIVER_H
