#include "MinimaxAlgorithm.h"
#include "GameUtils.h"
#include "Board.h"
#include <iostream>


struct MinimaxAlgorithm::Impl
{
    std::shared_ptr<Board> board { nullptr };
    uint step { 0 };
    const char __padding__[4] { 0 };  //!< for padding
};


MinimaxAlgorithm::MinimaxAlgorithm(const uint depth)
    : m_impl( new Impl )
    , m_depth( depth )
{
}

MinimaxAlgorithm::MinimaxAlgorithm()
    : MinimaxAlgorithm(1)
{   
}

Choice MinimaxAlgorithm::getChoice()
{    
    m_impl->board.reset( std::move(getBoard()->clone()) );
    m_impl->step = 0;

    return runMin().choice;
}

int MinimaxAlgorithm::minimax(const uint depth, const bool maximizing)
{
    if (depth == 0)
        return 1;

    auto&& emptyTileIds = m_impl->board->getFilteredIds( Tile::State::None );
    if (emptyTileIds.empty())
        return 1;

    const Tile::State state = maximizing
            ? Tile::State::User
            : Tile::State::Computer;

    const auto minScore = - static_cast<int>( m_impl->board->getSize() );
    const auto maxScore = + static_cast<int>( m_impl->board->getSize() );

    int score = maximizing ? minScore : maxScore;

    auto op = maximizing
            ? ([](int a, int b) -> int { return std::max(a, b); })
            : ([](int a, int b) -> int { return std::min(a, b); });

    for (auto&& id : emptyTileIds)
    {
        auto tile = m_impl->board->getTile( id );
        tile->setState( state );

        int score_ { 0 };
        if (GameUtils::isWon(m_impl->board.get(), state))
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

    if (m_impl->step == m_depth)
    {
        result.score = 0;
        return result;
    }

    ++m_impl->step;

    auto&& emptyTileIds = m_impl->board->getFilteredIds(Tile::State::None);
    if (emptyTileIds.empty())
    {
        result.score = 0;
        --m_impl->step;
        return result;
    }

    const auto maxScore = + static_cast<int>( m_impl->board->getSize() + 1 );
    const auto minScore = - maxScore;

    result.score = maxScore;

    for (auto&& id : emptyTileIds)
    {
        auto tile = m_impl->board->getTile(id);
        tile->setState(Tile::State::Computer);

        int score { 0 };


        if (GameUtils::isWon(m_impl->board.get(), Tile::State::Computer))
        {
            score = minScore;
            result.score = minScore + 1;
            result.choice.tileId = id;
            result.choice.isValid = true;
            tile->setState(Tile::State::None);
            --m_impl->step;
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

    --m_impl->step;
    return result;
}

MinimaxAlgorithm::Result MinimaxAlgorithm::runMax()
{
    Result result;

    if (m_impl->step == m_depth)
    {
        result.score = 0;
        return result;
    }

    ++m_impl->step;

    auto&& emptyTileIds = m_impl->board->getFilteredIds(Tile::State::None);
    if (emptyTileIds.empty())
    {
        result.score = 0;
        --m_impl->step;
        return result;
    }

    const auto maxScore = + static_cast<int>( m_impl->board->getSize() + 1 );
    const auto minScore = - maxScore;

    result.score = minScore;

    for (auto&& id : emptyTileIds)
    {
        auto tile = m_impl->board->getTile(id);
        tile->setState(Tile::State::User);

        int score { 0 };

        if (GameUtils::isWon(m_impl->board.get(), Tile::State::User))
        {
            score = maxScore;
            result.score = maxScore - 1;
            result.choice.tileId = id;
            result.choice.isValid = true;
            tile->setState(Tile::State::None);
            --m_impl->step;
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

    --m_impl->step;
    return result;
}

