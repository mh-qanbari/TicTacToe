#include "Board.h"


Board::Board(const uint size, QObject *parent)
    : QObject(parent)
    , m_size(size)
{
    initTiles();
}

Board::Board(const Board &other)
    : QObject(other.parent())
{
    *this = other;
}

Board::Board(Board &&other)
    : QObject(other.parent())
{
    *this = std::move( other );
}

Board &Board::operator=(const Board &other)
{
    clearTiles();

    m_size = other.m_size;
    for (auto&& tile : other.m_tiles)
    {
        m_tiles.push_back( new Tile(*tile) );
    }

    return *this;
}

Board &Board::operator=(Board &&other)
{
    m_size = 0;
    clearTiles();
    std::swap(m_size, other.m_size);
    std::swap(m_tiles, other.m_tiles);
    return *this;
}

Board *&&Board::clone() const
{
    return std::move( new Board(*this) );
}

void Board::reset()
{
    for (auto&& tile : m_tiles)
        tile->reset();
}

Tile *Board::getTile(const uint id) const
{
    auto&& position = getPositionOf( id );
    return getTile( position );
}

Tile *Board::getTile(const Position &position) const
{
    const uint index = getIndexOf(position);
    if ( index >= (m_size * m_size) )
        return nullptr;
    return m_tiles.at(index);
}

std::unordered_set<uint> Board::getFilteredIds(Tile::State state) const
{
    std::unordered_set<uint> ids;
    for (auto it = m_tiles.begin(); it != m_tiles.end(); ++it)
    {
        auto&& tile = *it;
        if ( tile->getState() == state )
            ids.insert( tile->getId() );
    }
    return ids;
}

void Board::clearTiles()
{
    while ( !m_tiles.empty() )
    {
        auto it = m_tiles.begin();
        (*it)->deleteLater();
        it = m_tiles.erase(it);
    }
}

void Board::initTiles()
{
    clearTiles();

    for (uint i = 0; i < (m_size * m_size) ; ++i)
    {
        auto&& tile = new Tile();

        tile->setId( i );
        tile->setPosition( getPositionOf(i) );
        tile->setState( Tile::State::None );

        m_tiles.emplace_back(tile);
    }
}
