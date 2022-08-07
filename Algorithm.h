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

    virtual void setBoard(Board *board);
    virtual Board *getBoard() const;

    virtual Choice getChoice() = 0;

private:
    Board *m_board { nullptr };
};


class RandomAlgorithm : public Algorithm
{
public:
    RandomAlgorithm(Board *board = nullptr)
        : Algorithm()
    {
        setBoard(board);
    }

    // Algorithm interface
    Choice getChoice() override;
};

#endif // ALGORITHM_H
