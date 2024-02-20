import QtQuick
import QtQuick.Controls

import ui.types

Rectangle {
    id: tile
    color: "yellow"
    enabled: state === Tile.Undefined
    property TileState state: Tile.Undefined
    IconLabel {
        anchors.fill: parent
        icon.source: getStateIcon(tile.state)
        function getStateIcon(state) {
            switch (state) {
                case Tile.X: return "icons/x.svg";
                case Tile.O: return "icons/o.svg";
                default: return "";
            }
        }
    }
}
