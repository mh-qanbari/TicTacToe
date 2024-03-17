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
    return true;
}
