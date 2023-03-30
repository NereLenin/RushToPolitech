#include "appback.h"

#include <QFile>

appBack::appBack(QObject *parent)
    : QObject{parent}
{

}

void appBack::readTicketsFromDB()
{

    for(int i=0; i<tickets.size();i++)
          printTicket(i);

}

void appBack::setPathToTicketsDB(QString pathToTicketDB)
{
    this->pathToTicketDB = pathToTicketDB;
}

void appBack::printTicket(int index)
{
    tickets[index]->debugPrint();
}

void appBack::askTicket(const Ticket &ticket)
{
    ticket.debugPrint();
}

void appBack::clearTickets()
{

}
