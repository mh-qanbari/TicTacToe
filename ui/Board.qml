import QtQuick

import ui.types
import ui

Item {
    id: root
    property int spacing: 10
    property int padding: 40
    readonly property int rows: BoardModel.rowCount()
    readonly property int columns: BoardModel.columnCount()
    readonly property real cellSize: (width - 2 * padding - spacing * (columns - 1)) / columns

    property PlayerFlag currentPlayer: Player.X

    TableView {
        anchors.fill: root
        anchors.margins: root.padding
        columnSpacing: root.spacing; rowSpacing: root.spacing

        model: BoardModel
        delegate: TileItem {
            id: tile
            implicitHeight: root.cellSize; implicitWidth: root.cellSize
            flag: display
            MouseArea {
                anchors.fill: parent
                enabled: tile.enabled
                onClicked: {
                    if (tile.flag !== Player.Undefined)
                        return
                    display = root.currentPlayer
                    root.currentPlayer = (root.currentPlayer === Player.X) ? Player.O : Player.X
                }
            }
        }
    }
}
