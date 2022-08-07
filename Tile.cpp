#include "Tile.h"


Tile::Tile(QObject *parent)
    : QObject(parent)
{
}

Tile::Tile() : Tile(nullptr)
{
}

Tile::Tile(const Tile &other)
    : Tile(other.parent())
{
    *this = other;
}

Tile &Tile::operator=(const Tile &other)
{
    m_state = other.m_state;
    m_position = other.m_position;

    return *this;
}
