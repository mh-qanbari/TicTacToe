#include "boardmodel.h"

using namespace ui;

BoardModel::BoardModel(QObject *parent)
    : QAbstractTableModel{parent}
{
    m_data.fill(PlayerFlag::Undefined);
}

int BoardModel::rowCount(const QModelIndex &parent) const
{
    (void)parent;
    return 3;
}

int BoardModel::columnCount(const QModelIndex &parent) const
{
    (void)parent;
    return 3;
}

QVariant BoardModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant{};
    return static_cast<int>(getTileFlag(index));
}

bool BoardModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    (void)role;
    if (!index.isValid())
        return false;
    const bool ok = setTileFlag(index, static_cast<PlayerFlag>(value.toInt()));
    if (ok)
        emit dataChanged(index, index, {role,});
    return ok;
}

QModelIndex BoardModel::index(int row, int column, const QModelIndex &parent) const
{
    if (parent.isValid())
        return QModelIndex{};
    return createIndex(row, column);
}

bool BoardModel::clearItemData(const QModelIndex &modelIndex)
{
    if (modelIndex.isValid()) {
        const int index = this->index(modelIndex);
        m_data[index] = PlayerFlag::Undefined;
        emit dataChanged(modelIndex, modelIndex, {});
    } else {
        for (auto it = m_data.begin(); it != m_data.end(); ++it)
            *it = PlayerFlag::Undefined;
        emit dataChanged(index(0, 0), index(rowCount(), columnCount()));
    }
    return true;
}

BoardModel *BoardModel::create(QQmlEngine *, QJSEngine *)
{
    if (s_instance == nullptr)
        s_instance = new BoardModel;
    return s_instance;
}

int BoardModel::index(const QModelIndex &modelIndex) const
{
    return modelIndex.row() * rowCount() + modelIndex.column();
}

PlayerFlag BoardModel::getTileFlag(const QModelIndex &modelIndex) const
{
    if (!modelIndex.isValid())
        return PlayerFlag::Undefined;
    return m_data.at(index(modelIndex));
}

bool BoardModel::setTileFlag(const QModelIndex &index, PlayerFlag state)
{
    if (!index.isValid())
        return false;
    m_data[this->index(index)] = state;
    if (isGameFinished(index))
        emit gameFinished(state);
    return true;
}

bool BoardModel::isGameFinished(const QModelIndex &modelIndex)
{
    const int row = modelIndex.row();
    const int column = modelIndex.column();
    const PlayerFlag player_sign = getTileFlag(modelIndex);

    // check row
    if ((player_sign == getTileFlag(index(row, 0))) &&
        (player_sign == getTileFlag(index(row, 1))) &&
        (player_sign == getTileFlag(index(row, 2))))
        return true;

    // check column
    else if ((player_sign == getTileFlag(index(0, column))) &&
             (player_sign == getTileFlag(index(1, column))) &&
             (player_sign == getTileFlag(index(2, column))))
        return true;

    // check orthogonal: top-left to bottom-right
    else if ((column == row) &&
             (player_sign == getTileFlag(index(0, 0))) &&
             (player_sign == getTileFlag(index(1, 1))) &&
             (player_sign == getTileFlag(index(2, 2))))
        return true;

    // check orthogonal: top-right to bottom-left
    else if ((column + row == 2) &&
             (player_sign == getTileFlag(index(0, 2))) &&
             (player_sign == getTileFlag(index(1, 1))) &&
             (player_sign == getTileFlag(index(2, 0))))
        return true;

    return false;
}
