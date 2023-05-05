#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "appengine.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    AppEngine appEngine(&app);

    QQmlApplicationEngine qmlEngine;
    appEngine.connectToEngine(&qmlEngine);

    const QUrl url(u"qrc:/qml/main.qml"_qs);
    QObject::connect(&qmlEngine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    qmlEngine.load(url);
    return app.exec();
}
