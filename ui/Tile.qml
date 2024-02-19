import QtQuick
import QtQuick.Controls

Rectangle {
    color: "yellow"
    property alias icon: iconLabel.icon
    IconLabel { id: iconLabel; anchors.fill: parent }
}
