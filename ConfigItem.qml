import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls.Styles 1.4


Item {
    id: root

    signal started()

    Rectangle {
        z: -1
        anchors.fill: parent
        color: style.background.level2
    }

    Style {
        id: style
    }

    SpinBox {
        id: spin_difficulty
        y: parent.height * 0.4
        x: (parent.width - width) / 2
        height: parent.height * 0.1
        width: parent.width * 0.8
        leftPadding: height + 5
        from: controller.getDifficulty().min
        to: controller.getDifficulty().max
        value: controller.getDifficulty().value

        textFromValue: function() { return controller.getDifficultyText(value) }

        contentItem: Label {
            horizontalAlignment: Label.AlignHCenter
            verticalAlignment: Label.AlignVCenter
            text: parent.textFromValue()
            color: style.item.color
            font.pixelSize: 30
        }

        background: Rectangle {
            anchors.fill: parent
            color: style.item.background
        }

        down.indicator: Button {
            height: parent.height
            width: height
            flat: true

            contentItem: Label {
                text: "\u25C4"
                horizontalAlignment: Label.AlignHCenter
                verticalAlignment: Label.AlignVCenter
                color: parent.enabled ? style.item.color : "gray"
                font.pixelSize: 20
            }

            background: Rectangle {
                anchors.fill: parent
                color: {
                    if (parent.pressed)
                        return style.background.level1
                    else
                        return style.background.level2
                }
            }

            onClicked: {
                const value = parent.value - controller.getDifficulty().step
                controller.setDifficulty(value)
                parent.value = value
            }
        }
        up.indicator: Button {
            anchors.right: parent.right
            height: parent.height
            width: height
            flat: true

            contentItem: Label {
                text: "\u25BA"
                horizontalAlignment: Label.AlignHCenter
                verticalAlignment: Label.AlignVCenter
                color: parent.enabled ? style.item.color : "gray"
                font.pixelSize: 20
            }

            background: Rectangle {
                anchors.fill: parent
                color: {
                    if (parent.pressed)
                        return style.background.level1
                    else
                        return style.background.level2
                }
            }

            onClicked: {
                const value = parent.value + controller.getDifficulty().step
                controller.setDifficulty(value)
                parent.value = value
            }
        }
    }

    Button {
        x: (parent.width - width) / 2
        y: spin_difficulty.y + spin_difficulty.height + parent.height * 0.05
        height: spin_difficulty.height * 1.3
        width: spin_difficulty.width - spin_difficulty.height * 2
        Layout.preferredHeight: 30
        Layout.fillWidth: true

        contentItem: Label {
            horizontalAlignment: Label.AlignHCenter
            verticalAlignment: Label.AlignVCenter
            text: "Start"
            color: style.item.color
            font.pixelSize: 40
            font.bold: true
        }

        onClicked: {
            started()
        }

        background: Rectangle {
            color: {
                return parent.pressed ? style.background.level1
                                      : style.background.level3
            }
        }
    }
}
