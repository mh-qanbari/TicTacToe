#include "Controller.h"
#include "Algorithm.h"
#include "GameUtils.h"
#include "MinimaxAlgorithm.h"
#include <QGuiApplication>


constexpr auto DIFFICULTY_STEP    = 3;
constexpr auto DIFFICULTY_MIN     = 1;
constexpr auto DIFFICULTY_DEFAULT = 4;
constexpr auto DIFFICULTY_MAX     = 7;

struct Controller::Impl
{
    ::Algorithm *algorithm  { nullptr };
    Controller::Algorithm alg { Controller::Alg_Minimax };
    uint difficulty { DIFFICULTY_DEFAULT };
    uint boardSize  { 3 };
    const char __padding__[4] { "" };
};


Controller::Controller(const uint size, Board *board, QObject *parent)
    : QObject(parent)
    , m_impl(new Impl)
    , m_board(board)
{
    Controller::register_qml();
    Tile::register_qml();

    m_impl->boardSize = size;
}

Controller::Controller()
    : Controller(3, nullptr, nullptr)
{
}

Controller::~Controller()
{
    if ( !m_impl->algorithm )
    {
        delete m_impl->algorithm;
        m_impl->algorithm = nullptr;
    }
}

Tile *Controller::getTile(const uint id) const
{
    return m_board->getTile(id);
}

Tile *Controller::getTile(const uint row, const uint col) const
{
    Position position;
    position.row = row;
    position.col = col;

    return m_board->getTile(position);
}

void Controller::setTileState(const uint id, const Tile::State state)
{
    if ( id >= (m_impl->boardSize * m_impl->boardSize) )
        return;

    auto&& tile = getTile(id);

    if (tile->getState() == Tile::State::None)
    {
        tile->setState(state);

        if (GameUtils::isWon(m_board, Tile::State::User))
        {
            emit gameFinished( Tile::State::User );
            return;
        }

        auto emptyTileIds = m_board->getFilteredIds(Tile::State::None);
        if ( emptyTileIds.empty() )
        {
            emit gameFinished(Tile::State::None);
            return;
        }

        auto&& choice = m_impl->algorithm->getChoice();
        if ( choice.isValid )
        {
            tile = getTile(choice.tileId);
            tile->setState(Tile::Computer);
            QCoreApplication::processEvents();
        }
        else
        {
            emit gameFinished(Tile::State::None);
            return;
        }

        if (GameUtils::isWon(m_board, Tile::State::Computer))
        {
            emit gameFinished( Tile::State::Computer );
            return;
        }
    }
}

QVariantMap Controller::getDifficulty() const
{
    QVariantMap difficulty;
    difficulty["valid"] = true;
    difficulty["value"] = m_impl->difficulty;
    difficulty["min"]   = DIFFICULTY_MIN;
    difficulty["max"]   = DIFFICULTY_MAX;
    difficulty["step"]  = DIFFICULTY_STEP;
    return difficulty;
}

QString Controller::getDifficultyText() const
{
    switch (m_impl->difficulty) {
    case DIFFICULTY_MIN:      return "Easy";
    case DIFFICULTY_DEFAULT:  return "Medium";
    case DIFFICULTY_MAX:      return "Hard";
    }
    return "Medium";
}

QVariantMap Controller::getAlgorithms() const
{
    QVariantMap algorithms;
    algorithms["list"] = QStringList({"random", "minimax"});
    algorithms["random"] = Alg_Random;
    algorithms["minimax"] = Alg_Minimax;
    return algorithms;
}

#include <QDebug>
void Controller::setDifficulty(uint difficulty)
{
    m_impl->difficulty = ((difficulty < DIFFICULTY_MIN)
                          ? DIFFICULTY_MIN
                          : ((difficulty > DIFFICULTY_MAX)
                             ? DIFFICULTY_MAX
                             : difficulty));
//    qDebug() << "difficulty: " << m_impl->difficulty;
}

void Controller::start()
{
    if (m_impl->algorithm)
    {
        delete m_impl->algorithm;
        m_impl->algorithm = nullptr;
    }

    //switch (m_impl->alg) {
    //case Alg_Random:
    //    m_impl->algorithm = new RandomAlgorithm { m_board };
    //    break;
    //case Alg_Minimax:
        m_impl->algorithm = new MinimaxAlgorithm { m_impl->difficulty };
        m_impl->algorithm->setBoard( m_board );
    //    break;
    //}
        qDebug() << "difficulty: " << m_impl->difficulty;

}

void Controller::reset()
{
    m_board->reset();
    emit resetGame();
}

void Controller::register_qml() const
{
    qRegisterMetaType<Controller::Algorithm>("Controller::Algorithm");
}
