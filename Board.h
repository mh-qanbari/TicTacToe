#ifndef BOARD_H
#define BOARD_H

#include "Tile.h"
#include <unordered_set>


class Board : public QObject
{
    Q_OBJECT

public:
    Board(const uint size, QObject *parent = nullptr);
    Board(const Board &);
    Board(Board &&);

    Board &operator=(const Board &);
    Board &operator=(Board &&);

    Board *&&clone() const;
    void reset();

    Tile *getTile(const uint id) const;
    Tile *getTile(const Position &position) const;
    std::unordered_set<uint> getFilteredIds(Tile::State) const;

    inline uint getSize() const;
    inline uint getIndexOf(const Position &position) const;
    inline Position getPositionOf(const uint id) const;

private:
    void clearTiles();
    void initTiles();

private:
    std::vector<Tile*> m_tiles {};
    uint m_size  { 3 };
    const char __padding__[4] { " "};  //!< for padding
};

uint Board::getSize() const
{
    return m_size;
}

uint Board::getIndexOf(const Position &position) const
{
    return m_size * position.row + position.col;
}

Position Board::getPositionOf(const uint id) const
{
    Position position;
    position.row = id / m_size;
    position.col = id % m_size;
    return position;
}

#endif // BOARD_H
