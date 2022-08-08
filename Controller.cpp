#include "Controller.h"
#include "Algorithm.h"
#include "GameUtils.h"
#include <QGuiApplication>


Controller::Controller(const uint size, Board *board,
                       Algorithm *algorithm, QObject *parent)
    : QObject(parent)
    , m_algorithm(algorithm)
    , m_board(board)
    , m_size(size)
{
    Tile::register_qml();
}

Controller::Controller()
    : Controller(3, nullptr, nullptr)
{
}

Controller::~Controller()
{
    if ( !m_algorithm )
    {
        delete m_algorithm;
        m_algorithm = nullptr;
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
    if ( id >= (m_size * m_size) )
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

        auto&& choice = m_algorithm->getChoice();
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
