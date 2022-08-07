#ifndef GAMEUTILS_H
#define GAMEUTILS_H

#include "Board.h"

class GameUtils final
{
private:
    GameUtils() = delete;

    static bool winRow(const Board *board, const uint id, Tile::State state);
    static bool winCol(const Board *board, const uint id, Tile::State state);
    static bool winDiags(const Board *board, const uint id, Tile::State state);

public:
    static bool isWon(const Board *board, Tile::State state);
};

#endif // GAMEUTILS_H
