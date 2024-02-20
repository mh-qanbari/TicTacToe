#ifndef UI_CONTROLLER_H
#define UI_CONTROLLER_H

#include <QObject>
#include <QQmlEngine>

namespace ui {
class Controller : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    QML_SINGLETON

public:
    static Controller *create();
    static Controller *create(QQmlEngine *, QJSEngine *);

private:
    explicit Controller(QObject *parent = nullptr);
    void registerTypes();

private:
    static inline Controller *s_instance {nullptr};
};
}

#endif // UI_CONTROLLER_H
