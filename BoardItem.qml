import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Layouts 1.12
import QtQuick.Dialogs 1.2

import Tile.State 1.0

Item {
    id: root

    Style {
        id: style
    }

    Rectangle {
        anchors.fill: parent
        color: style.background.color
        z: -1
    }

    GridLayout {
        columns: 3
        rows: 3

        anchors.centerIn: parent

        TileItem {
            Layout.column: 0
            Layout.row: 0
            model: controller.getTile(Layout.row, Layout.column);
        }
        TileItem {
            Layout.column: 1
            Layout.row: 0
            model: controller.getTile(Layout.row, Layout.column);
        }
        TileItem {
            Layout.column: 2
            Layout.row: 0
            model: controller.getTile(Layout.row, Layout.column);
        }


        TileItem {
            Layout.column: 0
            Layout.row: 1
            model: controller.getTile(Layout.row, Layout.column);
        }
        TileItem {
            Layout.column: 1
            Layout.row: 1
            model: controller.getTile(Layout.row, Layout.column);
        }
        TileItem {
            Layout.column: 2
            Layout.row: 1
            model: controller.getTile(Layout.row, Layout.column);
        }

        TileItem {
            Layout.column: 0
            Layout.row: 2
            model: controller.getTile(Layout.row, Layout.column);
        }
        TileItem {
            Layout.column: 1
            Layout.row: 2
            model: controller.getTile(Layout.row, Layout.column);
        }
        TileItem {
            Layout.column: 2
            Layout.row: 2
            model: controller.getTile(Layout.row, Layout.column);
        }
    }

    MessageDialog {
        id: messageDialog
        title: "Game is Finished"

        property int winner: 0

        text: {
            if (winner === Tile.User)
                return "User Won!"
            else if (winner === Tile.Computer)
                return "Game Over!"
            else
                return "Draw!"
        }

        onAccepted: {
            console.log(text)
            Qt.quit()
        }
    }

    Connections {
        target: controller
        onGameFinished: {
            messageDialog.winner = winner
            messageDialog.open()
        }
    }
}
