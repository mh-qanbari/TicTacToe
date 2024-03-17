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

protected:
    BoardModel(QObject *parent = nullptr);

public:
    // QAbstractItemModel interface
    virtual int rowCount(const QModelIndex &parent = QModelIndex{}) const override;
    virtual int columnCount(const QModelIndex &parent = QModelIndex{}) const override;
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    virtual bool setData(const QModelIndex &index,
                         const QVariant &value,
                         int role = Qt::DisplayRole) override;
    virtual QModelIndex index(int row, int column,
                              const QModelIndex &parent = QModelIndex{}) const override;

    //! -------------------------------------------------------------
    //! \brief instance returns the instance.
    //! \details the instance is nullptr if it has not been created yet.
    //! \return returns the instance
    static BoardModel *instance() { return s_instance; }
    static BoardModel *create(QQmlEngine *, QJSEngine *);

private:
    int index(const QModelIndex &index) const;
    TileState getTileState(const QModelIndex &index) const;
    bool setTileState(const QModelIndex &index, TileState state);
    bool isGameFinished(const QModelIndex &index);

signals:
    void gameFinished(TileState winner);

private:
    static inline BoardModel *s_instance = nullptr;
    std::array<TileState, 9> m_data;
};
}

#endif // BOARDMODEL_H
