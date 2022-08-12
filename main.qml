import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12

Window {
    visible: true
    width: 330
    height: 330
    title: qsTr("TicTacToe")
    flags: Qt.Dialog

    Style {
        id: style
    }

    Rectangle {
        z: -1
        color: style.background.level1
    }

    StackView {
        id: stack_view
        initialItem: view_board
        anchors.fill: parent
        Component.onCompleted: push(view_config)
    }

    Component {
        id: view_config

        ConfigItem {
            onStarted: {
                stack_view.pop()
                controller.start();
            }
        }
    }

    Component {
        id: view_board

        BoardItem {
            onResetRequested: {
                stack_view.push(view_config)
                controller.reset()
            }
            onReplayRequested: {
                controller.reset()
            }
        }
    }
}
