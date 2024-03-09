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

    Q_PROPERTY(DifficultyLevel level READ getLevel NOTIFY levelChanged FINAL)
    Q_PROPERTY(bool isGameStarted READ isGameStarted NOTIFY gameStateChanged FINAL)

public:
    Q_INVOKABLE QString difficultyText(DifficultyLevel level) const;
    Q_INVOKABLE void startGame(DifficultyLevel level);
    Q_INVOKABLE void stopGame();
    Q_INVOKABLE bool isGameStarted() const;

    static TicTacToe *create(QQmlEngine *, QJSEngine *);

protected:
    void setLevel(DifficultyLevel level);
    //! -------------------------------------------------------------
    //! \brief getLevel is the getter method for \a level property
    //! \details This method should be called when the game is started.
    //! For making sure that the game has already started, check the
    //! \link isGameStarted property; Otherwise, it throws exception.
    //! \return returns value of the \a level property
    DifficultyLevel getLevel() const noexcept(false);

signals:
    void levelChanged();
    void gameStateChanged();

private:
    static inline TicTacToe *s_instance {nullptr};
    std::optional<DifficultyLevel> m_level;
};
}

#endif // UI_TICTACTOE_H
