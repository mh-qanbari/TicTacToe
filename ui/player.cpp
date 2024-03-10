#include "player.h"
#include "boardmodel.h"

using namespace ui;

Player::Player(TileState sign, QObject *parent)
    : QObject{parent}
    , m_sign{sign}
{}

void Player::select(const QModelIndex &index)
{
    auto *board_model = BoardModel::instance();
    if (board_model == nullptr)
        return;
    board_model->setData(index, static_cast<int>(m_sign));
}

Player *Player::getPlayer(TileState sign)
{
    if (auto it = s_instances.find(sign); it != s_instances.end())
        return it->second;
    auto [it, ok] = s_instances.emplace(sign, new Player{sign});
    return ok ? it->second : nullptr;
}
