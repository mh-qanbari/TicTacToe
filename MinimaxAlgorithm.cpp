#include "MinimaxAlgorithm.h"
#include "Board.h"


MinimaxAlgorithm::MinimaxAlgorithm()
{   
}

MinimaxAlgorithm::MinimaxAlgorithm(const uint depth)
    : m_depth(depth)
{
}

Choice MinimaxAlgorithm::getChoice()
{
    m_workingBoard.reset( std::move(getBoard()->clone()) );

    int bestScore { - static_cast<int>(m_workingBoard->getSize()) };
    uint bestTileId { 0 };

    auto emptyTileIds = m_workingBoard->getFilteredIds( Tile::State::None );
    for (auto&& id : emptyTileIds)
    {
        auto tile = m_workingBoard->getTile( id );
        tile->setState( Tile::State::Computer );

        const int score = minimax( m_depth, true );
        if ( score > bestScore )
        {
            bestScore = score;
            bestTileId = id;
        }

        tile->setState( Tile::State::None );
    }

    Choice choice;
    choice.tileId = bestTileId;
    choice.isValid = true;
    return choice;
}

int MinimaxAlgorithm::minimax(const uint depth, const bool maximizing)
{
    if (depth == 0)
        return 1;

    auto&& emptyTileIds = m_workingBoard->getFilteredIds( Tile::State::None );
    if (emptyTileIds.empty())
        return 1;

    int score = maximizing
            ? - static_cast<int>( m_workingBoard->getSize() )
            : + static_cast<int>( m_workingBoard->getSize() );

    const Tile::State state = maximizing
            ? Tile::State::Computer
            : Tile::State::User;

    auto op = maximizing
            ? ([](int a, int b) -> int { return std::max(a, b); })
            : ([](int a, int b) -> int { return std::min(a, b); });

    for (auto&& id : emptyTileIds)
    {
        auto tile = m_workingBoard->getTile( id );
        tile->setState( state );
        score = op( score, minimax(depth - 1, false) );
        tile->setState( Tile::State::None );
    }

    return score;
}

