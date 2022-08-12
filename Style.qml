import QtQuick 2.12

QtObject {
    id: root

    readonly property var background: QtObject {
        readonly property color color: "#305799"

        readonly property color level1: "#806a00"
        readonly property color level2: "#8c7500"
        readonly property color level3: "#998000"
        readonly property color level4: "#ccaa00"
        readonly property color level5: "#e6bf00"
        readonly property color level6: "#ffd500"
    }
    readonly property var board: QtObject {
        readonly property color background: "yellow"
    }
    readonly property var tile: QtObject {
        readonly property color background: "#E5C550"
        readonly property color color: "#498ACB"
    }
}
