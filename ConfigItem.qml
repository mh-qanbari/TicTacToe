import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

Item {
    id: root

    signal started()

    Rectangle {
        z: -1
        anchors.fill: parent
        color: style.background.color
    }

    Style {
        id: style
    }

    GridLayout {
        rows: 4
        columns: 2
        anchors.fill: parent
        anchors.margins: 10

        Label {
            text: "Algorithm"
        }
        ComboBox {
            id: combo_algs
            Layout.fillWidth: true
            model: controller.getAlgorithms().list
            property var currentData: controller.getAlgorithms()[currentText]
            background: Rectangle {
                color: parent.hovered ? style.background.level5 : style.background.level4
            }
        }

        Label {
            text: "Difficulty"
        }
        SpinBox {
            id: spin_difficulty
            Layout.fillWidth: true
            enabled: controller.getDifficulty(combo_algs.currentData).valid
            from: controller.getDifficulty(combo_algs.currentData).min
            to: controller.getDifficulty(combo_algs.currentData).max
            value: controller.getDifficulty(combo_algs.currentData).value
            background: Rectangle {
                anchors.fill: parent
                color: parent.hovered ? style.background.level5 : style.background.level4
            }
            down.indicator: Button {
                height: parent.height
                width: height
                flat: true
                text: "-"
                hoverEnabled: true
                background: Rectangle {
                    anchors.fill: parent
                    color: {
                        if (parent.pressed)
                            return style.background.level3
                        else if (parent.hovered)
                            return style.background.level5
                        else
                            return style.background.level4
                    }
                }
                onClicked: {
                    parent.value -= 1
                }
            }
            up.indicator: Button {
                anchors.right: parent.right
                height: parent.height
                width: height
                flat: true
                text: "+"
                hoverEnabled: true
                background: Rectangle {
                    anchors.fill: parent
                    color: {
                        if (parent.pressed)
                            return style.background.level3
                        else if (parent.hovered)
                            return style.background.level5
                        else
                            return style.background.level4
                    }
                }
                onClicked: {
                    parent.value += 1
                }
            }
        }

        Item {
            Layout.columnSpan: 2
            Layout.fillHeight: true
            Layout.fillWidth: true
        }

        Item {
            Layout.fillWidth: true
        }
        Button {
            text: "Start"
            Layout.preferredHeight: 30
            Layout.fillWidth: true
            onClicked: {
                controller.setAlgorithm(combo_algs.currentData, spin_difficulty.value)
                started()
            }
            background: Rectangle {
                color: {
                    if (parent.pressed && parent.hovered)
                        return style.background.level1
                    else if (parent.pressed)
                        return style.background.level2
                    else if (parent.hovered)
                        return style.background.level4
                    else
                        return style.background.level3
                }
            }
        }
    }
}
