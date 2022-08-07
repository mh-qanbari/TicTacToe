#include "Algorithm.h"
#include "Board.h"



Algorithm::Algorithm()
{
}

Algorithm::~Algorithm()
{
    m_board = nullptr;
}

Choice RandomAlgorithm::getChoice()
{
    auto&& board = getBoard();
    if ( !board )
        return Choice();

    auto&& tileIds = board->getFilteredIds(Tile::None);
    if ( tileIds.empty() )
        return Choice();

    auto&& size = static_cast<int>(tileIds.size());

    srand(static_cast<unsigned>(time(nullptr)));
    const auto index = static_cast<size_t>(rand() % size);

    auto it = tileIds.begin();
    std::advance(it, index);

    Choice choice;
    choice.isValid = true;
    choice.tileId = *it;
    return choice;
}

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
