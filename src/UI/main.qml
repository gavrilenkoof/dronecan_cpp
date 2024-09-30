import QtQuick
import QtQuick.Controls

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    property var main: _main

    Button {
        id: testButton
        anchors.centerIn: parent
        text: "Click on me"
        onClicked: handle()
    }

    function handle()
    {
        console.log("from main", main.core.id)
        main.core.id = 10
//        main.core.connect()
    }

}
