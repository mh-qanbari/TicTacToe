#ifndef TILE_H
#define TILE_H

#include <QQmlEngine>

struct Position
{
    uint row { 0 };
    uint col { 0 };
};

class Tile : public QObject
{
    Q_OBJECT

    Q_PROPERTY(State state READ getState WRITE setState NOTIFY stateChanged)
    Q_PROPERTY(uint row READ getRow WRITE setRow NOTIFY rowChanged)
    Q_PROPERTY(uint col READ getCol WRITE setCol NOTIFY colChanged)
    Q_PROPERTY(uint id READ getId NOTIFY idChanged)

public:
    enum State : int {
        None = 0,
        User = 1,
        Computer = -1,
    }; Q_ENUMS(State)

private:
    State m_state {None};
    Position m_position;
    uint m_id  {0};

public:
    Tile(QObject *parent);
    Tile();
    Tile(const Tile &);

    Tile &operator=(const Tile &);

    Position getPosition() const
    {
        return m_position;
    }

    uint getRow() const
    {
        return m_position.row;
    }

    uint getCol() const
    {
        return m_position.col;
    }

    State getState() const
    {
        return m_state;
    }

    uint getId() const
    {
        return m_id;
    }

public slots:
    void setPosition(const Position &position)
    {
        setRow(position.row);
        setCol(position.col);
    }

    void setRow(uint row)
    {
        if (m_position.row == row)
            return;

        m_position.row = row;
        emit rowChanged(row);
    }

    void setCol(uint col)
    {
        if (m_position.col == col)
            return;

        m_position.col = col;
        emit colChanged(col);
    }

    void setState(State state)
    {
        if (m_state == state)
            return;

        m_state = state;
        emit stateChanged(m_state);
    }

    void setId(uint id)
    {
        if (m_id == id)
            return;

        m_id = id;
        emit idChanged(m_id);
    }

signals:
    void rowChanged(uint row);
    void colChanged(uint col);
    void stateChanged(State state);
    void idChanged(uint id);

public:
    static void register_qml()
    {
        qRegisterMetaType<Tile>("Tile");
        qRegisterMetaType<Tile::State>("Tile::State");
        qmlRegisterType<Tile>("Tile.State", 1, 0, "Tile");
    }
};

#endif // TILE_H
