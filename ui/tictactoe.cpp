#include "tictactoe.h"
#include "boardmodel.h"

using namespace ui;

TicTacToe *TicTacToe::create(QQmlEngine *qmlEngine, QJSEngine *jsEngine)
{
    if (!BoardModel::instance())
        BoardModel::create(qmlEngine, jsEngine);
    if (s_instance == nullptr)
        s_instance = new TicTacToe;
    s_instance->connect(BoardModel::instance(), &BoardModel::gameFinished,
                        s_instance, &TicTacToe::stopGame);
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
    if (!isGameStarted())
        throw ExceptionType::GameNotStarted;
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
    BoardModel::instance()->clearItemData();
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

const char *TicTacToe::Exception::what() const noexcept
{
    switch (m_type) {
    case ExceptionType::GameNotStarted: return "the game is not started.";
    default: break;
    }
    return "unknown exception is thown";
}
