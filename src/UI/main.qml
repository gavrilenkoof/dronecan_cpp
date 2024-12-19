import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
//import Qt.labs.platform
import QtQml

import ToolBox

ApplicationWindow {
    id: mainWindow
    width: 640
    height: 480
    visible: false
    title: qsTr("DroneCAN GUI Tool")

    color: dcPallete.window

    readonly property var dcPallete: ToolBox.pallete
    readonly property var linkManager : ToolBox.linkManager
    property var setup_window: undefined

    Component.onCompleted: spawnSetupWindow()

    function spawnSetupWindow()
    {
        var component = Qt.createComponent("setup.qml")
        setup_window = component.createObject(mainWindow)
        setup_window.closing.connect(setupWindowClose)
        setup_window.show()
    }

    function setupWindowClose()
    {
        setup_window.destroy()
        setup_window = undefined
        if(!mainWindow.visible)
        {
            visible = true
            mainWindow.close()
        }
    }

    Connections {
        target: linkManager
        function onConnectionSuccess()
        {
            setupWindowClose()
            mainWindow.visible = true
        }
    }




    MenuBar {
           id: menuBar

           Menu {
               id: toolsMenu
               title: qsTr("Tools")

               MenuItem {
                   text: qsTr("Bus monitor")
                   onTriggered: console.debug("Bus monitor item clicked")
               }
               MenuItem {
                   text: qsTr("Interactive console")
                   onTriggered: console.debug("Interactive console item clicked")
               }
               MenuItem {
                   text: qsTr("Subscriber")
                   onTriggered: console.debug("Subscriber item clicked")
               }
               MenuItem {
                   text: qsTr("Plotter")
                   onTriggered: console.debug("Plotter item clicked")
               }

           }

           Menu {
               id: panelsMenu
               title: qsTr("Panels")

               MenuItem {
                   text: qsTr("test")
                   onTriggered: console.debug("test item clicked")
               }
           }
           Menu {
               id: helpMenu
               title: qsTr("Help")

               MenuItem {
                   text: qsTr("Open DroneCAN website")
                   onTriggered: console.debug("Open DroneCAN website item clicked")
               }
           }
       }



    GridLayout {
        id: leftGrid
        columns: 1
        rows: 4

        anchors {
            top: menuBar.bottom
            left: menuBar.left
//            fill: parent
//            topMargin: 30
            margins: 5
        }

        rowSpacing: 0
        columnSpacing: 0

        Rectangle {
            id: localNodePropertiesRect
            color: mainWindow.color
            border.color: "red"

            Layout.row: 0
            Layout.column: 0
            Layout.preferredHeight: mainWindow.height * 0.07
            Layout.preferredWidth: mainWindow.width * 0.55
        }

        Rectangle {
            id: adapterSettingsRect
            color: mainWindow.color
            border.color: "blue"

            Layout.row: 1
            Layout.column: 0
            Layout.preferredHeight: mainWindow.height * 0.07
            Layout.preferredWidth: localNodePropertiesRect.width
        }

        Rectangle {
            id: nodeTableRect
            color: mainWindow.color
            border.color: "red"

            Layout.row: 2
            Layout.column: 0
            Layout.preferredHeight: mainWindow.height * 0.81
            Layout.preferredWidth: localNodePropertiesRect.width

        }

        Rectangle {
            id: fileServerRect
            color: mainWindow.color
            border.color: "yellow"

            Layout.row: 4
            Layout.column: 0
            Layout.preferredHeight: mainWindow.height * 0.05
            Layout.preferredWidth: localNodePropertiesRect.width
        }

//        Rectangle {
//            id: systemMsgRect
//            color: mainWindow.color
//            border.color: "red"

//            Layout.row: 5
//            Layout.column: 0
//            Layout.columnSpan: 2
//            Layout.preferredHeight: leftGrid.height * 0.05
//            Layout.preferredWidth: leftGrid.width
//        }


    }


//    GridLayout {
//        id: rightGrid

//        columns: 1
//        rows: 2

//        anchors {
//            top: menuBar.bottom
//            left: menuBar.right
//            fill: parent
//            topMargin: 30
//            margins: 5
//        }

//        rowSpacing: 0
//        columnSpacing: 0

//        Rectangle {
//            id: logMsgRect

//            color: mainWindow.color
//            border.color: "red"

//            Layout.row: 0
//            Layout.column: 0
//            Layout.preferredHeight: rightGrid.height * 0.4
//            Layout.preferredWidth: rightGrid.width * 0.45
//        }


//    }




}
