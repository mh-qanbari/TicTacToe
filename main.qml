import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12

Window {
    visible: true
    width: 400
    height: 400
    title: qsTr("TicTacToe")

    Style {
        id: style
    }

    Rectangle {
        z: -1
        color: style.background.color
    }

    StackView {
        id: stack_view
        initialItem: view_config
        anchors.fill: parent
    }

    Component {
        id: view_config

        ConfigItem {
            onStarted: {
                stack_view.push(view_board)
                controller.start();
            }
        }
    }

    Component {
        id: view_board

        BoardItem {
        }
    }
}
