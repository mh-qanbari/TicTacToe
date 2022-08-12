#include "Controller.h"
#include "Algorithm.h"
#include "MinimaxAlgorithm.h"
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    constexpr uint SIZE  { 3 };
    constexpr uint DEPTH { 6 };

    Board *board = new Board(SIZE);
    Controller controller { SIZE, board, &app };

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.rootContext()->setContextProperty("controller", &controller);
    engine.load(url);


    return app.exec();
}
