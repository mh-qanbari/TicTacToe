import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import ui

ApplicationWindow {
    width: 480
    height: 480
    visible: true
    title: qsTr("Tic Tac Toe")

    DefaultPage {
        anchors.fill: parent
        anchors.margins: 40
        visible: !TicTacToe.isGameStarted
    }

    Board {
        anchors.fill: parent
        padding: 40
        visible: TicTacToe.isGameStarted
    }
}
