import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Dialogs 1.2
import QtQuick.Window 2.12
import QtQuick.Layouts 1.12

Window {
    id: root
    minimumHeight: height
    maximumHeight: height
    minimumWidth: width
    maximumWidth: width
    //flags: Qt.SplashScreen
    flags: Qt.Dialog
    modality: Qt.ApplicationModal

    property string text: ""
    QtObject {
        id: response
        property bool accepted: false
    }

    signal quitRequested()
    signal resetRequested()
    signal replayRequested()
    signal rejected()
    signal accepted()


    Style {
        id: style
    }

    Rectangle {
        z: 0
        width: parent.width
        height: parent.height
        color: style.background.level3
    }

    ColumnLayout {
        anchors.fill: parent
        Label {
            id: text
            Layout.fillWidth: true
            Layout.preferredHeight: 30
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            text: root.text
            color: style.item.color
            font.bold: true
            font.pixelSize: 20
        }

        Item {
            Layout.fillWidth: true
            Layout.fillHeight: true

            RowLayout {
                anchors.fill: parent
                anchors.margins: 10

                Button {
                    Layout.fillWidth: true

                    contentItem: Label {
                        horizontalAlignment: Label.AlignHCenter
                        verticalAlignment: Label.AlignVCenter
                        text: "Quit!"
                        color: style.item.color
                        font.pixelSize: 20
                        font.bold: true
                    }

                    onClicked: {
                        response.accepted = true
                        root.quitRequested()
                        close()
                    }

                    background: Rectangle {
                        color: {
                            if (parent.pressed)
                                return style.background.level1
                            else
                                return style.background.level3
                        }
                    }
                }

                Button {
                    Layout.fillWidth: true

                    contentItem: Label {
                        horizontalAlignment: Label.AlignHCenter
                        verticalAlignment: Label.AlignVCenter
                        text: "Reset"
                        color: style.item.color
                        font.pixelSize: 20
                        font.bold: true
                    }

                    onClicked: {
                        response.accepted = true
                        root.resetRequested()
                        close()
                    }

                    background: Rectangle {
                        color: {
                            if (parent.pressed)
                                return style.background.level1
                            else
                                return style.background.level3
                        }
                    }
                }

                Button {
                    Layout.fillWidth: true

                    contentItem: Label {
                        horizontalAlignment: Label.AlignHCenter
                        verticalAlignment: Label.AlignVCenter
                        text: "Replay"
                        color: style.item.color
                        font.pixelSize: 20
                        font.bold: true
                    }

                    onClicked: {
                        response.accepted = true
                        root.replayRequested()
                        close()
                    }

                    background: Rectangle {
                        color: {
                            if (parent.pressed)
                                return style.background.level1
                            else
                                return style.background.level3
                        }
                    }
                }
            }
        }
    }

    onVisibleChanged: {
        if (visible === true) {
            response.accepted = false
            return
        }
        (response.accepted) ? accepted() : rejected()
    }
}
