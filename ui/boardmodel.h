#ifndef BOARDMODEL_H
#define BOARDMODEL_H

#include "Types.h"

#include <QAbstractTableModel>
#include <QQmlEngine>


namespace ui {
class BoardModel : public QAbstractTableModel
{
    Q_OBJECT
    QML_ELEMENT
    QML_SINGLETON

public:
    BoardModel(QObject *parent = nullptr);

    // QAbstractItemModel interface
    virtual int rowCount(const QModelIndex &parent = QModelIndex{}) const override;
    virtual int columnCount(const QModelIndex &parent = QModelIndex{}) const override;
    virtual QVariant data(const QModelIndex &index, int role) const override;

    static BoardModel *create(QQmlEngine *, QJSEngine *);

private:
    TileState getTileState(const QModelIndex &modelIndex) const;

private:
    static inline BoardModel *s_instance = nullptr;
    std::array<TileState, 9> m_data;
};
}

#endif // BOARDMODEL_H
