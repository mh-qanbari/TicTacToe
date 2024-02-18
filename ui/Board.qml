import QtQuick

Grid {
    id: grid
    rows: 3
    columns: 3
    spacing: 10
    padding: 10

    readonly property real cellSize: (width - padding*2 - spacing*(columns-1)) / columns

    Repeater {
        model: 9
        delegate: Tile { height: grid.cellSize; width: grid.cellSize }
    }
}
