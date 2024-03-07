#include "tictactoe.h"

using namespace ui;

TicTacToe *TicTacToe::create(QQmlEngine *, QJSEngine *)
{
    if (s_instance == nullptr)
        s_instance = new TicTacToe;
    return s_instance;
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

