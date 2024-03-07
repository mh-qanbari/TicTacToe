#ifndef UI_TICTACTOE_H
#define UI_TICTACTOE_H

#include "Types.h"
#include <QObject>
#include <QQmlEngine>

namespace ui {
class TicTacToe : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    QML_SINGLETON

public:
    Q_INVOKABLE QString difficultyText(DifficultyLevel level) const;

    static TicTacToe *create(QQmlEngine *, QJSEngine *);

private:
    static inline TicTacToe *s_instance {nullptr};
};
}

#endif // UI_TICTACTOE_H
