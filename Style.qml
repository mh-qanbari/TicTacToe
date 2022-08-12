import QtQuick 2.12

QtObject {
    id: root

    readonly property var background: QtObject {
        readonly property color level1: "#2D567F"
        readonly property color level2: "#305799"
        readonly property color level3: "#4079B2"
    }

    readonly property var item: QtObject {
        readonly property color background: "#4079B2"
        readonly property color color: "#E5C550"
    }

    readonly property var board: QtObject {
        readonly property color background: "yellow"
    }

    readonly property var tile: QtObject {
        readonly property color background: "#E5C550"
        readonly property color color: "#4079B2"//"#498ACB"
    }
}
