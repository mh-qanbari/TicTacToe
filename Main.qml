import QtQuick.Controls
import QtQuick.Layouts

import ui

ApplicationWindow {
    width: 640
    height: 480
    visible: true
    title: qsTr("Tic Tac Toe")

    DefaultPage {
        anchors.centerIn: parent
        width: parent.width * 0.5
        height: parent.height * 0.7
    }

    Board {
        anchors.centerIn: parent
        width: Math.min(parent.width, parent.height)
        height: width
        visible: false
    }
}
