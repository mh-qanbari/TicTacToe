import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import ui.types
import ui

Item {
    id: defaultPage

    ColumnLayout {
        id: layout
        anchors.fill: parent
        anchors.margins: 30
        spacing: 20
        Repeater {
            id: repeater
            model: Difficulty.Hard - Difficulty.Easy + 1
            Button {
                required property int index
                readonly property int level: Difficulty.Easy + index
                implicitHeight: (layout.height - layout.spacing * (repeater.count - 1)) / repeater.count
                implicitWidth: parent.width
                text: TicTacToe.difficultyText(level)
                Component.onCompleted: (index === 0) && forceActiveFocus()
            }
        }
    }
}
