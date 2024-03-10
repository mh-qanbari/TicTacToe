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
    return setTileState(index, static_cast<TileState>(value.toInt()));
}

BoardModel *BoardModel::create(QQmlEngine *, QJSEngine *)
{
    if (s_instance == nullptr)
        s_instance = new BoardModel;
    return s_instance;
}

TileState BoardModel::getTileState(const QModelIndex &index) const
{
    if (!index.isValid())
        return TileState::Undefined;
    return m_data.at(index.row() * rowCount() + index.column());
}

bool BoardModel::setTileState(const QModelIndex &index, TileState state)
{
    if (!index.isValid())
        return false;
    m_data[index.row() * rowCount() + index.column()] = state;
    return true;
}
