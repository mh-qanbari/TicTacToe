#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include "Types.h"

namespace ui {
class Player : public QObject
{
    Q_OBJECT

public:
    explicit Player(TileState sign, QObject *parent = nullptr);

    void select(const QModelIndex &);

    static Player *getPlayer(TileState sign);

private:
    static inline std::map<TileState, Player*> s_instances = {};
    TileState m_sign = TileState::Undefined;
};
}

#endif // PLAYER_H
