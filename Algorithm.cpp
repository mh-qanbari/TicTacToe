#include "Algorithm.h"
#include "Board.h"



Algorithm::Algorithm()
{
}

Algorithm::~Algorithm()
{
    m_board = nullptr;
}

Choice RandomAlgorithm::getChoice() const
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

    Choice choice;
    choice.isValid = true;
    choice.tileId = tileIds[index];
    return choice;
}
