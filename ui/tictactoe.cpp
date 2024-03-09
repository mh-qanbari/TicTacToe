#include "tictactoe.h"

using namespace ui;

TicTacToe *TicTacToe::create(QQmlEngine *, QJSEngine *)
{
    if (s_instance == nullptr)
        s_instance = new TicTacToe;
    return s_instance;
}

void TicTacToe::setLevel(DifficultyLevel level)
{
    if (m_level == level)
        return;
    m_level = level;
    emit levelChanged();
}

DifficultyLevel TicTacToe::getLevel() const
{
    assert(isGameStarted());
    return m_level.value_or(DifficultyLevel::Medium);
}

QString TicTacToe::difficultyText(DifficultyLevel level) const
{
    switch (level) {
    case DifficultyLevel::Easy: return "Easy";
    case DifficultyLevel::Medium: return "Medium";
    case DifficultyLevel::Hard: return "Hard";
    }
    return "";
}

void TicTacToe::startGame(DifficultyLevel level)
{
    setLevel(level);
    emit gameStateChanged();
}

void TicTacToe::stopGame()
{
    if (!m_level.has_value())
        return;
    m_level.reset();
    emit gameStateChanged();
}

bool TicTacToe::isGameStarted() const
{
    return m_level.has_value();
}
