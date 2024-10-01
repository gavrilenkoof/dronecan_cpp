import QtQuick
import QtQuick.Controls

ApplicationWindow {
    id: mainWindow
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    property var backend: _backend

    Button {
        id: testButton
        anchors.centerIn: parent
        text: "Click on me"
        onClicked: handle()
    }

    function handle()
    {
        console.log("from main", backend.id)
        backend.id = 10
    }

}
