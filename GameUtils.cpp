#include "GameUtils.h"


bool GameUtils::winRow(const Board *board, const uint id, Tile::State state)
{
    const uint size { board->getSize() };
    const uint matchSize { ((size == 3u) ? 3u : 4u) };
    const Position position { board->getPositionOf(id) };
    const uint minCol { (position.col > matchSize) ? (position.col - matchSize) : 0 };
    const uint maxCol { std::min(position.col + matchSize, size) };

    Position minPosition;
    minPosition.row = position.row;
    minPosition.col = minCol;

    Position maxPosition;
    maxPosition.row = position.row;
    maxPosition.col = maxCol;

    const uint minId { board->getIndexOf(minPosition) };
    const uint maxId { board->getIndexOf(maxPosition) };

    if ( size == 3 )
    {
        if ( (state == board->getTile(minId)->getState()) and
             (state == board->getTile(minId + 1)->getState()) and
             (state == board->getTile(minId + 2)->getState()) )
        {
            return true;
        }
    }
    else
    {
        for (uint id = minId; id < maxId - 3; ++id)
        {
            if ( (state == board->getTile(id)->getState()) and
                 (state == board->getTile(id + 1)->getState()) and
                 (state == board->getTile(id + 2)->getState()) and
                 (state == board->getTile(id + 3)->getState()) )
            {
                return true;
            }
        }
    }

    return false;
}

bool GameUtils::winCol(const Board *board, const uint id, Tile::State state)
{
    const uint size { board->getSize() };
    const uint matchSize { ((size == 3u) ? 3u : 4u) };
    const Position position { board->getPositionOf(id) };
    const uint minRow { (position.row > matchSize) ? (position.row - matchSize) : 0 };
    const uint maxRow { std::min(position.row + matchSize, size) };

    Position minPosition;
    minPosition.row = minRow;
    minPosition.col = position.col;

    Position maxPosition;
    maxPosition.row = maxRow;
    maxPosition.col = position.col;

    const uint minId { board->getIndexOf(minPosition) };

    if ( size == 3 )
    {
        if ( (state == board->getTile(minId)->getState()) and
             (state == board->getTile(minId + 3)->getState()) and
             (state == board->getTile(minId + 6)->getState()) )
        {
            return true;
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
            id = board->getIndexOf(position_);

            if ( (state == board->getTile(id)->getState()) and
                 (state == board->getTile(id)->getState()) and
                 (state == board->getTile(id)->getState()) and
                 (state == board->getTile(id)->getState()) )
            {
                return true;
            }
        }
    }

    return false;
}

bool GameUtils::winDiags(const Board *board, const uint id, Tile::State state)
{
    const uint size { board->getSize() };

    // top-left to bottom-right
    {
        if ( size == 3 )
        {
            if ( (state == board->getTile(0)->getState()) and
                 (state == board->getTile(4)->getState()) and
                 (state == board->getTile(8)->getState()) )
            {
                return true;
            }
        }
        else
        {
            const Position position { board->getPositionOf(id) };
            const uint back { std::min(position.row, position.col) };
            const uint front { size - std::max(position.row, position.col) };

            if ( (back + front) >= 4 )
            {
                const uint minRow { position.row - back };
                const uint maxRow { position.row + front };
                const uint minCol { position.col - back };

                for (uint row = minRow, col = minCol; row <= maxRow - 3; ++row, ++col)
                {
                    if ( (state == board->getTile({row, col})->getState()) and
                         (state == board->getTile({row+1, col+1})->getState()) and
                         (state == board->getTile({row+2, col+2})->getState()) and
                         (state == board->getTile({row+3, col+3})->getState()) )
                    {
                        return true;
                    }
                }
            }
        }
    }

    // top-right to bottom-left
    {
        if ( size == 3 )
        {
            if ( (state == board->getTile(2)->getState()) and
                 (state == board->getTile(4)->getState()) and
                 (state == board->getTile(6)->getState()) )
            {
                return true;
            }
        }
        else
        {
            const Position position { board->getPositionOf(id) };
            const uint back { std::min(position.row, size - position.col) };
            const uint front { std::min(size - position.row, position.col) };

            if ( (back + front) >= 4)
            {
                const uint minRow { position.row - back };
                const uint maxRow { position.row + front };
                const uint maxCol { position.col + back };

                for (uint row = minRow, col = maxCol; row <= maxRow - 3; ++row, --col)
                {
                    if ( (state == board->getTile({row, col})->getState()) and
                         (state == board->getTile({row+1, col-1})->getState()) and
                         (state == board->getTile({row+2, col-2})->getState()) and
                         (state == board->getTile({row+3, col-3})->getState()) )
                    {
                        return true;
                    }
                }
            }
        }
    }

    return false;
}

bool GameUtils::isWon(const Board *board, Tile::State state)
{
    if (state == Tile::State::None)
        return false;

    auto&& ids = board->getFilteredIds(state);
    for (auto&& id : ids)
    {
        if ( winRow(board, id, state) or
             winCol(board, id, state) or
             winDiags(board, id, state) )
        {
            return true;
        }
    }

    return false;
}
