#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "Board.h"
#include <QObject>
#include <memory>


class Controller : public QObject
{
    Q_OBJECT

public:
    enum Algorithm : int {
        Alg_Random = 1,
        Alg_Minimax,
    }; Q_ENUMS(Controller::Algorithm)

public:
    Controller(const uint size,
               Board *board = nullptr,
               QObject *parent = nullptr);
    Controller();
    ~Controller() override;

protected:
    Q_INVOKABLE Tile *getTile(const uint id) const;
    Q_INVOKABLE Tile *getTile(const uint row, const uint col) const;
    Q_INVOKABLE void setTileState(const uint id, const Tile::State state);
    Q_INVOKABLE QVariantMap getDifficulty(Controller::Algorithm) const;
    Q_INVOKABLE QVariantMap getAlgorithms() const;
    Q_INVOKABLE void setAlgorithm(Controller::Algorithm alg, uint difficulty);
    Q_INVOKABLE void start();

private:
    void register_qml() const;
    static constexpr uint GetRowOf(const uint id);
    static constexpr uint GetColOf(const uint id);
    static constexpr uint GetIndexOf(const uint row, const uint col);

signals:
    void gameFinished(Tile::State winner) const;

private:
    struct Impl;
    std::unique_ptr<Impl> m_impl;
    Board *m_board { nullptr };
};

#endif // CONTROLLER_H
