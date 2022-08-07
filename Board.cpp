#include "Board.h"

Board::Board(const uint size, QObject *parent)
    : QObject(parent)
    , m_size(size)
    , m_size2(size * size)
{
    initTiles();
}

Tile *Board::getTile(const Position &position) const
{
    const uint index = getIndexOf(position);
    if ( index >= m_size2 )
        return nullptr;
    return m_tiles.at(index);
}

std::vector<uint> Board::getFilteredIds(Tile::State state) const
{
    std::vector<uint> ids;
    for (auto it = m_tiles.begin(); it != m_tiles.end(); ++it)
    {
        auto&& tile = *it;
        if ( tile->getState() == state )
            ids.push_back( tile->getId() );
    }
    return ids;
}

void Board::initTiles()
{
    while ( !m_tiles.empty() )
    {
        auto it = m_tiles.begin();
        (*it)->deleteLater();
        it = m_tiles.erase(it);
    }

    const uint size_2 { m_size * m_size };

    for (uint i = 0; i < size_2 ; ++i)
    {
        auto&& tile = new Tile();

        tile->setId( i );
        tile->setPosition( getPositionOf(i) );
        tile->setState( Tile::State::None );

        m_tiles.emplace_back(tile);
    }
}
