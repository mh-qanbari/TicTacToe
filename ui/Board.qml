import QtQuick

Grid {
    id: grid
    anchors.fill: parent
    rows: 3
    columns: 3
    spacing: 10
    padding: 10

    property real cellWidth: (width - padding*2 - spacing*(columns-1)) / columns
    property real cellHeight: (height - padding*2 - spacing*(rows-1)) / rows

    Repeater {
        model: 9
        delegate: Rectangle {
            id: cellRect
            height: grid.cellHeight
            width: grid.cellWidth
            color: "yellow"
        }
    }
}
