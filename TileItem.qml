import QtQuick 2.12
import QtGraphicalEffects 1.0

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
            color: style.tile.color
            transform: rotation
            antialiasing: true
            z: icon.z
            scale: icon.scale

        }
        Rectangle {
            id: rect
            anchors.fill: parent
            //visible: root.model ? root.model.state === Tile.None : true
            color: style.tile.background
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
                // [test]
                if (mouse.button === Qt.RightButton)
                    root.model.state = Tile.Computer;
            }
        }
    }

//    property real radius: 2
//
//    Rectangle {
//        id: rect_fill
//        radius: root.radius
//        anchors.fill: parent
//        color: taphandler.pressed ? "white" : "gray"
//    }
//
//    Rectangle {
//        id: rect_border
//        radius: root.radius
//        anchors.fill: parent
//        border.color: hoverhandler.hovered ? "green" : rect_fill.color
//        border.width: hoverhandler.hovered ? 3 : 1
//        color: "transparent"
//    }
//
//    TapHandler {
//        id: taphandler
//    }
//
//    HoverHandler {
//        id: hoverhandler
//    }
}
