import QtQuick
import QtQuick.Layouts

import ui

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Tic Tac Toe")

    Board {
        anchors.centerIn: parent
        width: Math.min(parent.width, parent.height)
        height: width
    }
}
