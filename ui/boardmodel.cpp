#include "boardmodel.h"

using namespace ui;

BoardModel::BoardModel(QObject *parent)
    : QAbstractTableModel{parent}
{
    m_data.fill(TileState::Undefined);
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
    return static_cast<int>(getTileState(index));
}

bool BoardModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    (void)role;
    if (!index.isValid())
        return false;
    const bool ok = setTileState(index, static_cast<TileState>(value.toInt()));
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

TileState BoardModel::getTileState(const QModelIndex &modelIndex) const
{
    if (!modelIndex.isValid())
        return TileState::Undefined;
    return m_data.at(index(modelIndex));
}

bool BoardModel::setTileState(const QModelIndex &index, TileState state)
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
    const TileState player_sign = getTileState(modelIndex);

    // check row
    if ((player_sign == getTileState(index(row, 0))) &&
        (player_sign == getTileState(index(row, 1))) &&
        (player_sign == getTileState(index(row, 2))))
        return true;

    // check column
    else if ((player_sign == getTileState(index(0, column))) &&
             (player_sign == getTileState(index(1, column))) &&
             (player_sign == getTileState(index(2, column))))
        return true;

    // check orthogonal: top-left to bottom-right
    else if ((column == row) &&
             (player_sign == getTileState(index(0, 0))) &&
             (player_sign == getTileState(index(1, 1))) &&
             (player_sign == getTileState(index(2, 2))))
        return true;

    // check orthogonal: top-right to bottom-left
    else if ((column + row == 2) &&
             (player_sign == getTileState(index(0, 2))) &&
             (player_sign == getTileState(index(1, 1))) &&
             (player_sign == getTileState(index(2, 0))))
        return true;

    return false;
}
