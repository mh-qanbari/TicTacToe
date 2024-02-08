import QtQuick 2.12
import Qt5Compat.GraphicalEffects

import Tile.State 1.0

Item {
    id: root
    width: 100
    height: 100

    property Tile model: null

    Style {
        id: style
    }

    Item {
        anchors.fill: parent

        Image {
            id: icon
            anchors.fill: parent
            visible: root.model ? root.model.state !== Tile.None : false
            source: {
                if ( !root.model )
                    return ""

                switch (root.model.state) {
                case Tile.User:
                    return "qrc:/icons/icons/x.png"
                case Tile.Computer:
                    return "qrc:/icons/icons/o.png"
                default:
                    break
                }
                return ""
            }
            z:2
            scale: 0.8
            antialiasing: true
        }

        ColorOverlay{
            anchors.fill: icon
            source: icon
            color: style.tile.background
            transform: rotation
            antialiasing: true
            z: icon.z
            scale: icon.scale

        }

        Rectangle {
            id: rect
            anchors.fill: parent
            color: root.model && root.model.state === Tile.None
                   ? style.tile.background : style.tile.color
            radius: 10
            z:1
        }

        MouseArea {
            anchors.fill: parent
            enabled: root.model && root.model.state === Tile.None
            acceptedButtons: Qt.LeftButton | Qt.RightButton
            z:2

            onClicked: {
                if ( !root.model ) {
                    console.log("invalid tile model")
                    return
                }

                controller.setTileState(root.model.id, Tile.User);
            }
        }
    }
}
