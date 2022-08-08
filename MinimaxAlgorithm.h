#ifndef MINIMAXALGORITHM_H
#define MINIMAXALGORITHM_H

#include "Algorithm.h"
#include <memory>


class MinimaxAlgorithm : public Algorithm
{
public:
    MinimaxAlgorithm(const uint depth);
    MinimaxAlgorithm();

    uint getDepth() const { return m_depth; }
    void setDepth(const uint &depth) { m_depth = depth; }

    // Algorithm interface
    Choice getChoice() override;

private:
    int minimax(const uint depth, const bool maximizing);
    struct Result;
    Result runMin();
    Result runMax();

private:
    struct Working;
    std::unique_ptr<Working> m_working;
    uint m_depth { 1 };
    const char __padding__[4] { "" };  //!< for padding
};

struct MinimaxAlgorithm::Result
{
    int score { 0 };
    Choice choice;
};

#endif // MINIMAXALGORITHM_H
