#ifndef TICKETSDATABASEREADER_H
#define TICKETSDATABASEREADER_H
#include <QString>
#include <QList>
#include <QFile>

#include <QJsonParseError>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include <src/ticketbase.h>
#include <src/tickets.h>

class TicketBase;

class TicketsDataBaseReader
{
private:
    TicketsDataBaseReader();
    static void clearListOfTickets(QList<Ticket*>& listOfTickets);
public:
    static void readTicketsFromJsonDB(QString pathToJsonDB, TicketBase &baseInto);
    virtual ~TicketsDataBaseReader(){ }
};

#endif // TICKETSDATABASEREADER_H
