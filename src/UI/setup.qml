import QtQuick
import QtQuick.Controls
import QtQuick.Layouts


Window {
    id: setupWindow
    width: 460
    height: 420
    visible: true
    color: "#3a3a3a"
    title: qsTr("Application setup")

    readonly property var core : _tools.core

//    Rectangle {
//        id: rect
//        width: setupWindow.width * 0.7
//        height: setupWindow.height * 0.7
//        color: setupWindow.color
//        border.color: "red"
//    }

    GridLayout {
        id: grid
        columns: 1
        rows: 3
//        anchors.horizontalCenter: setupWindow.horizontalCenter
//        anchors.center: setupWindow.center

        Repeater {
            model: 2
            Rectangle {
                width: setupWindow.width * 0.9
                height: setupWindow.height * 0.3
                color: setupWindow.color
                border.color: "red"
            }
        }


    }

}


