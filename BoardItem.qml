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
        color: style.background.level2
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

    signal resetRequested()
    signal replayRequested()
    FinishDialog {
        id: finishDialog
        width: root.width
        height: root.height * 0.3
        onQuitRequested: Qt.quit()
        onResetRequested: root.resetRequested()
        onReplayRequested: root.replayRequested()
        onRejected: Qt.quit()
    }
    Connections {
        target: controller
        onGameFinished: {
            finishDialog.text =
                    (winner === Tile.User)
                    ? "User Won!"
                    : (winner === Tile.Computer)
                      ? "Game Over!"
                      : "Draw!"
            console.log("state: ", finishDialog.text)

            finishDialog.show()
        }
    }
}
