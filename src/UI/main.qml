import QtQuick
import QtQuick.Controls

import ToolBox

ApplicationWindow {
    id: mainWindow
    width: 640
    height: 480
    visible: true
    title: qsTr("DroneCAN GUI Tool")

    color: dcPallete.window

    readonly property var dcCore: ToolBox.core
    readonly property var dcPallete: ToolBox.pallete


    property var wnd: undefined

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

    Button {
        id: testButton
        anchors.centerIn: parent
        text: "Click on me"
        onClicked: handle()
    }

    function handle()
    {
        if(wnd == undefined)
        {
            var component = Qt.createComponent("setup.qml")
            wnd = component.createObject(mainWindow);
            wnd.closing.connect(function() { mainWindow.wnd = undefined;});
            wnd.show();
        }
        else
        {
            wnd.requestActivate();
        }
    }

}
