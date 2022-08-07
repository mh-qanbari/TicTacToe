#ifndef MINIMAXALGORITHM_H
#define MINIMAXALGORITHM_H

#include "Algorithm.h"
#include <memory>


class MinimaxAlgorithm : public Algorithm
{
public:
    MinimaxAlgorithm();

    uint getDepth() const { return m_depth; }
    void setDepth(const uint &depth) { m_depth = depth; }

    // Algorithm interface
    Choice getChoice() override;

private:
    int minimax(const uint depth, const bool maximizing);

private:
    std::shared_ptr<Board> m_workingBoard { nullptr };
    uint m_depth { 1 };
    const char __padding__[4] { "" };  //!< for padding
};

#endif // MINIMAXALGORITHM_H
