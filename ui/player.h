#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include "Types.h"

namespace ui {
class Player : public QObject
{
    Q_OBJECT

public:
    explicit Player(PlayerFlag sign, QObject *parent = nullptr);

    void select(const QModelIndex &);
    
    static Player *getPlayer(PlayerFlag sign);

private:
    static inline std::map<PlayerFlag, Player*> s_instances = {};
    PlayerFlag m_sign = PlayerFlag::Undefined;
};
}

#endif // PLAYER_H
