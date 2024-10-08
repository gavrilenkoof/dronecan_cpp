import QtQuick
import QtQuick.Controls

import ToolBox

ApplicationWindow {
    id: mainWindow
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    color: dcPallete.window

    readonly property var dcCore: ToolBox.core
    readonly property var dcPallete: ToolBox.pallete

    Button {
        id: testButton
        anchors.centerIn: parent
        text: "Click on me"
        onClicked: handle()
    }

    function handle()
    {
        dcCore.connect()
    }

}
