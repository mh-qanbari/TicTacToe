#ifndef BOARD_H
#define BOARD_H

#include "Tile.h"

//template<>
//struct std::hash<Tile>
//{
//    std::size_t operator()(const Tile &tile) const noexcept
//    {
//        return tile.getId();
//    }
//};

//template<>
//struct std::equal_to<Tile>
//{
//    bool operator()(const Tile &tile1, const Tile &tile2) const noexcept
//    {
//        return tile1.getId() == tile2.getId();
//    }
//};

class Board : public QObject
{
    Q_OBJECT

public:
    Board(const uint size = 3, QObject *parent = nullptr);

    Tile *getTile(const Position &position) const;
    std::vector<uint> getFilteredIds(Tile::State) const;

    inline uint getSize() const;
    inline uint getIndexOf(const Position &position) const;
    inline Position getPositionOf(const uint index) const;

private:
    void initTiles();

private:
    //std::unordered_map<uint, Tile*> m_tiles {};
    std::vector<Tile*> m_tiles {};
    const uint m_size  { 3 };
    const uint m_size2 { m_size * m_size };
};

uint Board::getSize() const
{
    return m_size;
}

uint Board::getIndexOf(const Position &position) const
{
    return m_size * position.row + position.col;
}

Position Board::getPositionOf(const uint index) const
{
    Position position;
    position.row = index / m_size;
    position.col = index % m_size;
    return position;
}

#endif // BOARD_H
