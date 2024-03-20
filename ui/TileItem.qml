import QtQuick
import QtQuick.Controls

import ui.types

Rectangle {
    id: tile
    color: "yellow"
    enabled: flag === Player.Undefined
    property PlayerFlag flag: Player.Undefined
    IconLabel {
        anchors.fill: parent
        icon.source: getStateIcon(tile.flag)
        function getStateIcon(state) {
            switch (state) {
                case Player.X: return "icons/x.svg";
                case Player.O: return "icons/o.svg";
                default: return "";
            }
        }
    }
}
