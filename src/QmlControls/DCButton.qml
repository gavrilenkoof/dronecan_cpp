import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import ToolBox

//import QGroundControl.Palette
//import QGroundControl.ScreenTools

Button {
    id: control
    text: qsTr("")

    readonly property var dcPallete : ToolBox.pallete

    property bool   _showHighlight:     enabled && (pressed | checked)

    contentItem: Text {
        id: text
        text: control.text
        font: control.font
        opacity: enabled ? 1.0 : 0.3
        color: dcPallete.text
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        elide: Text.ElideRight
    }

    background: Rectangle {
        id: backRect
        implicitHeight: control.height
        implicitWidth: control.width
        border.width: 1
        border.color: dcPallete.buttonBorder
        color: dcPallete.button

        Rectangle {
            anchors.fill: parent
            color: dcPallete.buttonHighlight
            opacity: _showHighlight ? 1 : control.enabled && control.hovered ? .3 : 0
        }


    }
}
