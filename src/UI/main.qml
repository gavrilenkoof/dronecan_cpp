import QtQuick
import QtQuick.Controls

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



//    function spawn_setup()
//    {
//        if(setup_window == undefined)
//        {
//            var component = Qt.createComponent("setup.qml")
//            setup_window = component.createObject(mainWindow);
//            setup_window.closing.connect(setupWindowClose);
//            setup_window.show();
//        }
//        else
//        {
//            setup_window.requestActivate();
//        }
//    }

}
