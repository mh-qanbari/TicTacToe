#include "boardmodel.h"

using namespace ui;

BoardModel::BoardModel(QObject *parent)
    : QAbstractTableModel(parent)
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

BoardModel *BoardModel::create(QQmlEngine *, QJSEngine *)
{
    if (s_instance == nullptr)
        s_instance = new BoardModel;
    return s_instance;
}

TileState BoardModel::getTileState(const QModelIndex &modelIndex) const
{
    if (!modelIndex.isValid())
        return TileState::Undefined;
    return m_data.at(modelIndex.row() * rowCount() + modelIndex.column());
}
