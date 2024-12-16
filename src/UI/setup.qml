import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQml

import QmlControls
import ToolBox




Window {
    id: setupWindow
    title: qsTr("Application setup")

    width: 460
    height: 420
    minimumWidth: 360
    minimumHeight: 360
    visible: true

    color: dcPallete.window

    readonly property var linkManager : ToolBox.linkManager
    readonly property var dcPallete : ToolBox.pallete

//    property var ports: ToolBox.core.link.ports


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

                    Text {
                        id: textSelector
                        color: dcPallete.text

                        anchors {
                            left: parent.left
                            bottom: parent.bottom
                        }

                        text: qsTr("Select CAN Interface")

                    }

                }

                Rectangle {
                    id: serialComboBoxRect
                    color: setupWindow.color

                    implicitHeight: selectSerial.height * 0.5
                    implicitWidth: selectSerial.width


                    DCComboBox {
                        id: serialComboBox

                        implicitHeight: selectSerial.height * 0.5
                        implicitWidth: selectSerial.width

                        Connections {
                            target: linkManager

                            function onPortsChanged()
                            {
                                var serialPorts = []
                                var index = 0
                                for(var port_desc in linkManager.ports)
                                {
                                    serialPorts.push(port_desc)
                                }

                                if(serialPorts.length === 0)
                                {
                                    index = -1
                                }

                                serialComboBox.model = serialPorts
                                serialComboBox.currentIndex = index

                            }

                        }
                    }



                }

            }

        }

        Rectangle {
            id: settingsAdapterRect
            color: setupWindow.color
//            border.color: "red"

            Layout.preferredHeight: mainGrid.height * 0.82
            Layout.preferredWidth: mainGrid.width

            ColumnLayout {
                spacing: 0
                anchors {
//                    horizontalCenter: parent.horizontalCenter
                    top: parent.top
                    verticalCenter: parent.verticalCenter
                }

                Rectangle {
                    id: textSettingsRect
                    color: setupWindow.color
//                    border.color: "yellow"
                    Layout.preferredHeight: settingsAdapterRect.height * 0.07
                    Layout.preferredWidth: settingsAdapterRect.width

                    Text {
                        id: textSettings
                        color: dcPallete.text

                        anchors {
                            left: parent.left
                            verticalCenter: parent.verticalCenter
                        }

                        text: qsTr("Adapter settings")
                    }


                }

                Rectangle {
                    id: settingsRect
                    color: dcPallete.windowBackground
//                    border.color: "blue"
                    Layout.preferredHeight: settingsAdapterRect.height * 0.9
                    Layout.preferredWidth: settingsAdapterRect.width
                    Layout.topMargin: 5

                    ColumnLayout {
                        spacing: 5
                        anchors {
                            top: parent.top
                            horizontalCenter: parent.horizontalCenter
                            topMargin: 5
                        }

                        Rectangle {
                            id: busNumberRect
                            color: dcPallete.windowBackground
//                            border.color: "red"


                            implicitHeight: settingsRect.height * 0.10
                            implicitWidth: settingsRect.width * 0.94

                            Text {
                                id: busNumberText
                                anchors {
                                    left: parent.left
                                    verticalCenter: parent.verticalCenter
                                }

                                color: dcPallete.text
                                text: qsTr("Bus number")
                            }

                            SpinBox {
                                id: busNumberSpinBox
                                anchors {
                                    right: parent.right
                                    verticalCenter: parent.verticalCenter
                                }
                                width: parent.width * 0.4
                                height: parent.height * 0.8
                            }


                        }

                        Rectangle {
                            id: canBusBitrateRect
                            color: busNumberRect.color
                            implicitHeight: busNumberRect.height
                            implicitWidth: busNumberRect.width
//                            border.color: "red"


                            Text {
                                id: canBusBitrateText
                                anchors {
                                    left: parent.left
                                    verticalCenter: parent.verticalCenter
                                }

                                color: dcPallete.text
                                text: qsTr("CAN bus bitrate")
                            }

                            SpinBox {
                                id: canBusBitrateSpinBox
                                anchors {
                                    right: parent.right
                                    verticalCenter: parent.verticalCenter
                                }
                                width: busNumberSpinBox.width
                                height: busNumberSpinBox.height
                                editable: true
                                from: 0
                                to: 1000000
                                value: 500000


                            }

                        }

                        Rectangle {
                            id: adapterBaudRateRect

                            color: busNumberRect.color
                            implicitHeight: busNumberRect.height
                            implicitWidth: busNumberRect.width


                            Text {
                                id: adapterBaudRateText
                                anchors {
                                    left: parent.left
                                    verticalCenter: parent.verticalCenter
                                }

                                color: dcPallete.text
                                text: qsTr("Adapter baudrate")
                            }

                            DCComboBox{
                                id: adapterBaudRateComboBox
                                anchors {
                                    right: parent.right
                                    verticalCenter: parent.verticalCenter
                                }

                                textHorizontalAlignment: Text.AlignHCenter

                                implicitHeight: busNumberSpinBox.height
                                implicitWidth: busNumberSpinBox.width

                                Component.onCompleted: {
                                    var bauds = ["57600", "115200", "1000000", "3000000"]

                                    adapterBaudRateComboBox.model = bauds
                                    adapterBaudRateComboBox.currentIndex = 3
                                }

                            }


                        }

                    }

                }


            }

        }

        Rectangle {
            id: acceptBtnRect
            color: setupWindow.color
//            border.color: "red"

            Layout.preferredHeight: mainGrid.height * 0.06
            Layout.preferredWidth: mainGrid.width

            DCButton {
                id: acceptBtn

                implicitWidth: parent.width
                implicitHeight: parent.height

                text: "OK"

                onClicked: connectionHandler()


                function connectionHandler()
                {
                    var portName = linkManager.ports[serialComboBox.currentValue]
                    var busNumber = busNumberSpinBox.value
                    var canBusBitrate = canBusBitrateSpinBox.value
                    var adapterSpeed = adapterBaudRateComboBox.currentValue
                    linkManager.makeConnection(portName, busNumber, canBusBitrate, adapterSpeed)
                }

            }




        }


    }

}


