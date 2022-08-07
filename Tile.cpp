#include "Tile.h"


Tile::Tile(QObject *parent)
    : QObject(parent)
{
}

Tile::Tile(const Tile &other)
    : Tile(other.parent())
{
    *this = other;
}

Tile::Tile(Tile &&other)
    : Tile(other.parent())
{
    *this = std::move( other );
}

Tile &Tile::operator=(const Tile &other)
{
    m_id = other.m_id;
    m_state = other.m_state;
    m_position = other.m_position;

    return *this;
}

Tile *&&Tile::clone() const
{
    return std::move( new Tile(*this) );
}
