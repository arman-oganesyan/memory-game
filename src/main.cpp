#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "gamemodel.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);
    GameModel gameModel;
    QQmlApplicationEngine engine;

    if (auto pContext = engine.rootContext())
        pContext->setContextProperty("gameModel", &gameModel);

    const QUrl url(QStringLiteral("qrc:/src/MemoryGameWindow.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
