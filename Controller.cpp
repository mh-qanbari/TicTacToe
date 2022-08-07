#include "Controller.h"
#include "Algorithm.h"
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
    Position&& position = m_board->getPositionOf(id);
    return m_board->getTile(position);
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

        if ( check(id) )
            return;

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

        if ( check(choice.tileId) )
            return;
    }
}

bool Controller::check(uint id) const
{
    const auto&& position = m_board->getPositionOf(id);
    return check( position );
}

bool Controller::check(const Position &position) const
{
    if ( checkRow(position) )
        return true;
    else if ( checkCol(position) )
        return true;
    else if ( checkDiags(position) )
        return true;



    return false;
}

bool Controller::checkRow(const Position &position) const
{
    const uint matchSize { ((m_size == 3u) ? 3u : 4u) };

    const uint minCol { (position.col > matchSize) ? (position.col - matchSize) : 0 };
    const uint maxCol { std::min(position.col + matchSize, m_size) };

    Position minPosition;
    minPosition.row = position.row;
    minPosition.col = minCol;

    Position maxPosition;
    maxPosition.row = position.row;
    maxPosition.col = maxCol;

    const uint minId { m_board->getIndexOf(minPosition) };
    const uint maxId { m_board->getIndexOf(maxPosition) };

    if ( m_size == 3 )
    {
        const auto&& state = getTile(minId)->getState();
        if ( state != Tile::State::None )
        {
            if ( (state == getTile(minId + 1)->getState()) and
                 (state == getTile(minId + 2)->getState()) )
            {
                emit gameFinished(state);
                return true;
            }
        }
    }
    else
    {
        for (uint id = minId; id < maxId - 3; ++id)
        {
            const auto&& state = getTile(id)->getState();

            if ( state == Tile::State::None )
                continue;

            if ( state != getTile(id + 1)->getState() )
                continue;

            if ( state != getTile(id + 2)->getState() )
                continue;

            if ( state != getTile(id + 3)->getState() )
                continue;

            emit gameFinished( state );
            return true;
        }
    }

    return false;
}

bool Controller::checkCol(const Position &position) const
{
    const uint matchSize { ((m_size == 3u) ? 3u : 4u) };

    const uint minRow { (position.row > matchSize) ? (position.row - matchSize) : 0 };
    const uint maxRow { std::min(position.row + matchSize, m_size) };

    Position minPosition;
    minPosition.row = minRow;
    minPosition.col = position.col;

    Position maxPosition;
    maxPosition.row = maxRow;
    maxPosition.col = position.col;

    const uint minId { m_board->getIndexOf(minPosition) };
    //const uint maxId { m_board->getIndexOf(maxPosition) };

    if ( m_size == 3 )
    {
        const auto&& state = getTile(minId)->getState();
        if ( state != Tile::State::None )
        {
            if ( (state == getTile(minId + 3)->getState()) and
                 (state == getTile(minId + 6)->getState()) )
            {
                emit gameFinished(state);
                return true;
            }
        }
    }
    else
    {
        Position position_;
        position_.col = position.col;
        uint id { 0 };

        for (uint row = minRow; row < maxRow - 3; ++row)
        {
            position_.row = row;
            id = m_board->getIndexOf(position_);

            const auto&& state = getTile(id)->getState();
            if ( state == Tile::State::None )
                continue;

            position_.row = row + 1;
            id = m_board->getIndexOf(position_);
            if ( state != getTile(id)->getState() )
                continue;

            position_.row = row + 2;
            id = m_board->getIndexOf(position_);
            if ( state != getTile(id)->getState() )
                continue;

            position_.row = row + 3;
            id = m_board->getIndexOf(position_);
            if ( state != getTile(id)->getState() )
                continue;

            emit gameFinished( state );
            return true;
        }
    }

    return false;
}

bool Controller::checkDiags(const Position &position) const
{
    // top-left to bottom-right
    {
        if ( m_size == 3 )
        {
            const auto&& state = getTile(0)->getState();
            if ( state != Tile::State::None )
            {
                if ( (state == getTile(4)->getState()) and
                     (state == getTile(8)->getState()) )
                {
                    emit gameFinished( state );
                    return true;
                }
            }
        }
        else
        {
            const uint back { std::min(position.row, position.col) };
            const uint front { m_size - std::max(position.row, position.col) };

            if ( (back + front) >= 4 )
            {
                const uint minRow { position.row - back };
                const uint maxRow { position.row + front };

                const uint minCol { position.col - back };
                //const uint maxCol { position.col + front };

                for (uint row = minRow, col = minCol; row <= maxRow - 3; ++row, ++col)
                {
                    const auto&& state = getTile(row, col)->getState();
                    if ( state == Tile::State::None )
                        continue;

                    if ( state != getTile(row + 1, col + 1)->getState() )
                        continue;

                    if ( state != getTile(row + 2, col + 2)->getState() )
                        continue;

                    if ( state != getTile(row + 3, col + 3)->getState() )
                        continue;

                    emit gameFinished( state );
                    return true;
                }
            }
        }
    }

    // top-right to bottom-left
    {
        if ( m_size == 3 )
        {
            const auto&& state = getTile(2)->getState();
            if ( state != Tile::State::None )
            {
                if ( (state == getTile(4)->getState()) and
                     (state == getTile(6)->getState()) )
                {
                    emit gameFinished( state );
                    return true;
                }
            }
        }
        else
        {
            const uint back { std::min(position.row, m_size - position.col) };
            const uint front { std::min(m_size - position.row, position.col) };
            if ( (back + front) >= 4)
            {
                const uint minRow { position.row - back };
                const uint maxRow { position.row + front };

                //const uint minCol { position.col - front };
                const uint maxCol { position.col + back };

                for (uint row = minRow, col = maxCol; row <= maxRow - 3; ++row, --col)
                {
                    const auto&& state = getTile(row, col)->getState();
                    if ( state == Tile::State::None )
                        continue;

                    if ( state != getTile(row + 1, col - 1)->getState() )
                        continue;

                    if ( state != getTile(row + 2, col - 2)->getState() )
                        continue;

                    if ( state != getTile(row + 3, col - 3)->getState() )
                        continue;

                    emit gameFinished( state );
                    return true;
                }
            }
        }
    }

    return false;
}
