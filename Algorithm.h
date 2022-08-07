#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <QtGlobal>


class Board;

struct Choice
{
    bool isValid { false };
    uint tileId { 0 };
};

class Algorithm
{
public:
    Algorithm();
    virtual ~Algorithm();

    inline void setBoard(Board *board);
    inline Board *getBoard() const;

    virtual Choice getChoice() const = 0;

private:
    Board *m_board { nullptr };
};

void Algorithm::setBoard(Board *board)
{
    if (m_board == board)
        return;
    m_board = board;
}

Board *Algorithm::getBoard() const
{
    return m_board;
}


class RandomAlgorithm : public Algorithm
{
public:
    RandomAlgorithm(Board *board = nullptr)
        : Algorithm()
    {
        setBoard(board);
    }

    // Algorithm interface
    Choice getChoice() const override;
};

#endif // ALGORITHM_H
