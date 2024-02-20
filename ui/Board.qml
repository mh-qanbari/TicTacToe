import QtQuick

import ui.types

Grid {
    id: grid
    rows: 3
    columns: 3
    spacing: 10
    padding: 10

    readonly property real cellSize: (width - padding*2 - spacing*(columns-1)) / columns

    Repeater {
        model: 9
        delegate: TileItem {
            id: tile
            height: grid.cellSize; width: grid.cellSize
            MouseArea {
                anchors.fill: parent
                enabled: tile.enabled
                onClicked: tile.state = index % 2 === 0 ? Tile.X : Tile.O
            }
        }
    }
}
