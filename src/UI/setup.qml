import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import ToolBox
import DCPallete

Window {
    id: setupWindow
    title: qsTr("Application setup")

    width: 460
    height: 420
    minimumWidth: 360
    minimumHeight: 360
    visible: true

    color: dcPal.darkWindow

    DCPallete {
        id: dcPal
    }

    readonly property var core : ToolBox.core


    GridLayout {
        id: mainGrid
        columns: 1
        rows: 3
        rowSpacing: 5

        anchors {
            margins: 20
            fill: parent
        }

        Rectangle {
            id: selectSerial

            color: setupWindow.color
//            border.color: "red"

//            Layout.bottomMargin: 10
//            implicitHeight: mainGrid.height * 0.12
//            implicitWidth: mainGrid.width
            Layout.preferredHeight: mainGrid.height * 0.12
            Layout.preferredWidth: mainGrid.width

            ColumnLayout {
//                spacing: 5
                anchors {
                    horizontalCenter: parent.horizontalCenter
                    verticalCenter: parent.verticalCenter
                }

                Rectangle {
                    id: textSelectorRect
                    color: setupWindow.color

                    implicitHeight: selectSerial.height * 0.3
                    implicitWidth: selectSerial.width
//                    Layout.fillWidth: true
//                    Layout.preferredHeight: selectSerial.height * 0.3

                    Text {
                        id: textSelector
                        color: dcPal.text

                        anchors {
                            left: parent.left
                            bottom: parent.bottom
                        }

                        text: qsTr("Select CAN Interface")

                    }

                }

                Rectangle {
                    id: comboBoxRect
                    color: setupWindow.color

                    implicitHeight: selectSerial.height * 0.5
                    implicitWidth: selectSerial.width
//                    Layout.fillWidth: true
//                    Layout.preferredHeight: selectSerial.height * 0.3


                    ComboBox {
                        id: comboBox

                        implicitHeight: selectSerial.height * 0.5
                        implicitWidth: selectSerial.width

                    }

                }

            }

        }

        Rectangle {
            id: settingsSerial
            color: setupWindow.color
            border.color: "red"

//            implicitHeight: mainGrid.height * 0.82
//            implicitWidth: mainGrid.width
            Layout.preferredHeight: mainGrid.height * 0.82
            Layout.preferredWidth: mainGrid.width

        }

        Rectangle {
            id: acceptBtnRect
            color: setupWindow.color
//            border.color: "red"

//            implicitHeight: mainGrid.height * 0.06
//            implicitWidth: mainGrid.width
            Layout.preferredHeight: mainGrid.height * 0.06
            Layout.preferredWidth: mainGrid.width

            Button {
                id: acceptBtn

                width: parent.width
                height: parent.height

                text: "OK"
                palette.buttonText: dcPal.text
            }


        }


    }

}


