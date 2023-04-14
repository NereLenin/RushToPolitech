#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <appengine.h>
#include <exclamations.h>

int main(int argc, char *argv[])
{

    AppEngine myEngine;

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    myEngine.connectToEngine(&engine);

    const QUrl url(u"qrc:/qml/main.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    //AppEngine myEngine(&engine,&app);
    engine.load(url);
    return app.exec();
}
