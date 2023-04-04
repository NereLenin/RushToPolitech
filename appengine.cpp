#include "appengine.h"

void AppEngine::bindQMLSlotSignalConnections(QObject *rootObject)
{
    if(rootObject==nullptr)
    {
        qDebug() << "try slot/signal connection with null rootObject";
        return;
    }

    //соединяем сигнал выбора ответа на форме с слотом записи в статистику
    QObject::connect(rootObject,SIGNAL(saveAnswerInStatistic(int,bool)),
                     this,SLOT(onSaveAnswerInStatistic(int,bool)));

    //соединяем сигнал начала сессии "учить" с слотом-контроллером этого режима
    QObject::connect(rootObject,SIGNAL(startLearningSession()),
                     this,SLOT(learnController()));

}

AppEngine::AppEngine(QObject *parent, QQmlApplicationEngine *engine)
    : QObject{parent}
{
    this->engine = engine;

    teacher.setTicketBase(&base);

    this->engine->rootContext()->setContextProperty("appEngine",this);

    bindQMLSlotSignalConnections(this->engine->rootObjects()[0]);
}

void AppEngine::emitPushSignalForTicket(Ticket *ticket)
{

    switch(ticket->getType())
    {
        case TicketType::selectableAnswerTicket:
        {
            SelectableAnswerTicket *currentTicket = dynamic_cast<SelectableAnswerTicket*>(ticket);
            emit pushSelectable(currentTicket->getIndex(), currentTicket->getQuestionText(),currentTicket->getImageUrl(),
                                  currentTicket->getAnswer(0),currentTicket->getAnswerImageUrl(0),
                                  currentTicket->getAnswer(1),currentTicket->getAnswerImageUrl(1),
                                  currentTicket->getAnswer(2),currentTicket->getAnswerImageUrl(2),
                                  currentTicket->getAnswer(3),currentTicket->getAnswerImageUrl(3),
                                  currentTicket->getIndexOfCorrectAnswer());
        }
        break;
    case TicketType::inputAnswerTicket:
    {
        InputAnswerTicket *currentTicket = dynamic_cast<InputAnswerTicket*>(ticket);
        emit pushInputable(currentTicket->getIndex(),currentTicket->getCorrectAnswer(),currentTicket->getQuestionText(), currentTicket->getImageUrl());
    }
    break;

    }

}

void AppEngine::learnController()
{
    //нам нужна статистика за сессию
    //Teacher() . sta
    QList tickets = base.getRandomTicketList(TicketStatus::Unlearned,10);

    if(tickets.size() == 0)
    {
        qDebug() << "Пушим нулевой билет";
       emit pushSelectable(0,"Нет больше билетов брат...\nПрости брат....\n","qrc:/icons/logo.png","Спасибо......\n я понял брат.....","","Ты чо попутал я за\n тебя 0 руб заплатил....","","","","","",1);
       return;
    }
    emit pushStack("FinishLearnScreen.qml");

    for(int i=0;i<tickets.size();i++)
    {
        emitPushSignalForTicket(tickets[i]);
    }
}

void AppEngine::onSaveAnswerInStatistic(int index, bool isCorrect)
{
    qDebug() << "слот на бэке ind: " << index << "correctness " << isCorrect;
    base.saveAnswerInStatistic(index,(TicketAnswerType)isCorrect);
    base.updateStatisticInBase();
}
