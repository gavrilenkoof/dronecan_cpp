import QtQuick
import QtQuick.Controls


ApplicationWindow {
    id: setupWindow
    width: 460
    height: 420
    visible: true
    title: qsTr("Application setup")

    readonly property var core : _tools.core

    Button {
        id: testButton
        anchors.centerIn: parent
        text: "Click on me"
        onClicked: make_connect()
    }


    function make_connect()
    {
        console.log(core.id)
//        console.log("from setup", backend.id)
//        backend.id = 5
//        setup.core.connect()
    }
}


