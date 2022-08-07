#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "Board.h"
#include <QObject>


class Algorithm;

class Controller : public QObject
{
    Q_OBJECT

public:
    Controller(const uint size,
               Board *board = nullptr,
               Algorithm *algorithm = nullptr,
               QObject *parent = nullptr);
    Controller();
    ~Controller() override;

protected:
    Q_INVOKABLE Tile *getTile(const uint id) const;
    Q_INVOKABLE Tile *getTile(const uint row, const uint col) const;
    Q_INVOKABLE void setTileState(const uint id, const Tile::State state);

private:
    bool check(uint id) const;
    bool check(const Position &position) const;
    bool checkRow(const Position &position) const;
    bool checkCol(const Position &position) const;
    bool checkDiags(const Position &position) const;

    static constexpr uint GetRowOf(const uint id);
    static constexpr uint GetColOf(const uint id);
    static constexpr uint GetIndexOf(const uint row, const uint col);

signals:
    void gameFinished(Tile::State winner) const;

private:
    Algorithm *m_algorithm { nullptr };
    Board *m_board { nullptr };
    const uint m_size  { 3 };
};

#endif // CONTROLLER_H
