import QtQuick
import QtQuick.Controls
import DronecanSetup



Window {
    id: setupWindow
    width: 460
    height: 420
    visible: true
    title: qsTr("Application setup")

    readonly property var setup: _setup

    Button {
        id: testButton
        anchors.centerIn: parent
        text: "Click on me"
        onClicked: make_connect()
    }


    function make_connect()
    {

        console.log("from setup", setup.core.id)
        setup.core.id = 5
//        setup.core.connect()
    }
}


