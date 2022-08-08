#include "MinimaxAlgorithm.h"
#include "GameUtils.h"
#include "Board.h"
#include <iostream>


struct MinimaxAlgorithm::Working
{
    std::shared_ptr<Board> board { nullptr };
    uint step { 0 };
    const char __padding__[4] { 0 };  //!< for padding
};


MinimaxAlgorithm::MinimaxAlgorithm(const uint depth)
    : m_working( new Working )
    , m_depth( depth )
{
}

MinimaxAlgorithm::MinimaxAlgorithm()
    : MinimaxAlgorithm(1)
{   
}

Choice MinimaxAlgorithm::getChoice()
{    
    m_working->board.reset( std::move(getBoard()->clone()) );
    m_working->step = 0;


    // -- new version
    return runMin().choice;


    // -- old version
    //int bestScore { static_cast<int>(m_working->board->getSize() + 1) };
    //uint bestTileId { 0 };
    //bool isValid { false };
    //
    //auto emptyTileIds = m_working->board->getFilteredIds( Tile::State::None );
    //if (emptyTileIds.empty())
    //    return Choice();
    //
    //for (auto&& id : emptyTileIds)
    //{
    //    auto tile = m_working->board->getTile( id );
    //    tile->setState( Tile::State::Computer );
    //
    //    const int score = minimax( m_depth, true );
    //    if ( score < bestScore )
    //    {
    //        bestScore = score;
    //        bestTileId = id;
    //        isValid = true;
    //    }
    //
    //    tile->setState( Tile::State::None );
    //}
    //
    //Choice choice;
    //choice.tileId = bestTileId;
    //choice.isValid = isValid;
    //return choice;
}

int MinimaxAlgorithm::minimax(const uint depth, const bool maximizing)
{
    if (depth == 0)
        return 1;

    auto&& emptyTileIds = m_working->board->getFilteredIds( Tile::State::None );
    if (emptyTileIds.empty())
        return 1;

    const Tile::State state = maximizing
            ? Tile::State::User
            : Tile::State::Computer;

    const auto minScore = - static_cast<int>( m_working->board->getSize() );
    const auto maxScore = + static_cast<int>( m_working->board->getSize() );

    int score = maximizing ? minScore : maxScore;

    auto op = maximizing
            ? ([](int a, int b) -> int { return std::max(a, b); })
            : ([](int a, int b) -> int { return std::min(a, b); });

    for (auto&& id : emptyTileIds)
    {
        auto tile = m_working->board->getTile( id );
        tile->setState( state );

        int score_ { 0 };
        if (GameUtils::isWon(m_working->board.get(), state))
            score_ = minScore;//maximizing ? minScore : maxScore;
        else
            score_ = minimax(depth - 1, !maximizing);

        score = op( score, score_ );
        tile->setState( Tile::State::None );
    }

    return score;
}

MinimaxAlgorithm::Result MinimaxAlgorithm::runMin()
{
    Result result;

    if (m_working->step == m_depth)
    {
        result.score = 0;
        return result;
    }

    ++m_working->step;

    auto&& emptyTileIds = m_working->board->getFilteredIds(Tile::State::None);
    if (emptyTileIds.empty())
    {
        result.score = 0;
        --m_working->step;
        return result;
    }

    const auto maxScore = + static_cast<int>( m_working->board->getSize() + 1 );
    const auto minScore = - maxScore;

    result.score = maxScore;

    for (auto&& id : emptyTileIds)
    {
        auto tile = m_working->board->getTile(id);
        tile->setState(Tile::State::Computer);

        int score { 0 };


        if (GameUtils::isWon(m_working->board.get(), Tile::State::Computer))
        {
            score = minScore;
            // TODO: no need to continue.
            result.score = minScore + 1;
            result.choice.tileId = id;
            result.choice.isValid = true;
            tile->setState(Tile::State::None);
            --m_working->step;
            return result;
        }
        else
        {
            score = runMax().score;
        }

        tile->setState(Tile::State::None);

        if (score < result.score)
        {
            result.score = score;
            result.choice.tileId = id;
            result.choice.isValid = true;
        }
    }

    --m_working->step;
    return result;
}

MinimaxAlgorithm::Result MinimaxAlgorithm::runMax()
{
    Result result;

    if (m_working->step == m_depth)
    {
        result.score = 0;
        return result;
    }

    ++m_working->step;

    auto&& emptyTileIds = m_working->board->getFilteredIds(Tile::State::None);
    if (emptyTileIds.empty())
    {
        result.score = 0;
        --m_working->step;
        return result;
    }

    const auto maxScore = + static_cast<int>( m_working->board->getSize() + 1 );
    const auto minScore = - maxScore;

    result.score = minScore;

    for (auto&& id : emptyTileIds)
    {
        auto tile = m_working->board->getTile(id);
        tile->setState(Tile::State::User);

        int score { 0 };

        if (GameUtils::isWon(m_working->board.get(), Tile::State::User))
        {
            score = maxScore;
            // TODO: no need to continue
            result.score = maxScore - 1;
            result.choice.tileId = id;
            result.choice.isValid = true;
            tile->setState(Tile::State::None);
            --m_working->step;
            return result;
        }
        else
        {
            score = runMin().score;
        }

        tile->setState(Tile::State::None);

        if (score > result.score)
        {
            result.score = score;
            result.choice.tileId = id;
            result.choice.isValid = true;
        }
    }

    --m_working->step;
    return result;
}
