#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <appengine.h>
//#include "src/tickets.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;


    const QUrl url(u"qrc:/qml/main.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    AppEngine myEngine(&engine);
    engine.load(url);

    //myEngine.bindQMLSlotSignalConnections();

    return app.exec();
}
