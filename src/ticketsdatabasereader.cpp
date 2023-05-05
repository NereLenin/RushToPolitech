#include "ticketsdatabasereader.h"

TicketsDataBaseReader::TicketsDataBaseReader()
{

}

void TicketsDataBaseReader::clearListOfTickets(QList<Ticket *> &listOfTickets)
{
    for(int i=0;i<listOfTickets.size();i++)
        delete listOfTickets[i];

    listOfTickets.clear();
}

//вот эту хуйню распилить на функции
//чтение файла в JsonDoc
//парс в лист
void TicketsDataBaseReader::readTicketsFromJsonDB(QString pathToJsonDB, TicketBase &baseInto)
{
    //нада ли если читается дальше файлом и если шо ошибка буит там
    if(pathToJsonDB == "" ) // \\ проверка на существование файла в qrc
    {
        //исключение путь нулевой до ебучей базы
        return;
    }

    QFile ticketsJSONfile(pathToJsonDB);

    if(!ticketsJSONfile.open( QIODevice::ReadOnly ))
    {
        //исключение нет файла с базой
        qDebug() << "не читается файл ебать";
        return;
    }

    QJsonParseError error;
    QJsonDocument ticketsDocument = QJsonDocument::fromJson(ticketsJSONfile.readAll(),&error);
    ticketsJSONfile.close();

    if(error.error != QJsonParseError::NoError)
            {
                //исключение не парсится файл с базой
                qDebug() << "Ошибка чтения БД";
                qDebug() << error.errorString();
                return;
            }
    //read end
    QJsonArray jsonTickets = ticketsDocument.object().value("tickets").toArray();
    baseInto.baseVersion = ticketsDocument.object().value("version").toDouble();

    //сначала проверить пустой ли файл, если есть че читать тогда чистим
    clearListOfTickets(baseInto.ticketsBase);


    //loadArrayToTicketsList
    QJsonObject jsonTicket;
    for(int i = 0; i < jsonTickets.size(); i++)
    {
        jsonTicket = jsonTickets[i].toObject();

        if(jsonTicket.isEmpty())
        {
            qDebug() << "ошибка парса на" << i;
            return;
        }

        Ticket *currentTicket = Ticket::createTicket(jsonTicket);

        baseInto.ticketsBase.append(currentTicket);
    }

    qDebug() << "Loaded" << baseInto.ticketsBase.size() << "tickets, baseName|version:" << ticketsDocument.object().value("name").toString() << "|" << baseInto.baseVersion;
}


