import QtQuick
import QtQuick.Controls

import ToolBox
import DCPallete

ApplicationWindow {
    id: mainWindow
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    color: dcPal.darkWindow

    DCPallete {
        id: dcPal
    }

    property var core: ToolBox.core

    Button {
        id: testButton
        anchors.centerIn: parent
        text: "Click on me"
        onClicked: handle()
    }

    function handle()
    {
        core.connect()
    }

}
