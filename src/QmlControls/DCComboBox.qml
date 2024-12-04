import QtQuick
import QtQuick.Window
import QtQuick.Controls

import ToolBox

ComboBox {
    id: control

    readonly property var dcPallete : ToolBox.pallete


    contentItem: Text {
        leftPadding: 5

        text: control.displayText
        font: control.font
        color: dcPallete.text
        verticalAlignment: Text.AlignVCenter
        elide: Text.ElideRight
    }

    delegate: ItemDelegate {
        id: delegate

        required property var model
        required property int index

        width: control.width

        contentItem: Text {
            text: delegate.model[control.textRole]
            color: dcPallete.text
            font: control.font
            elide: Text.ElideRight
            verticalAlignment: Text.AlignVCenter
        }

        background: Rectangle {
            color: dcPallete.button
        }

        MouseArea {
            anchors.fill: parent
            hoverEnabled: true

            onEntered: {
                delegate.background.color = dcPallete.buttonHighlight; // Change background color on hover
            }

            onExited: {
                delegate.background.color = dcPallete.button; // Reset background color after hover
            }

            onClicked: {
                control.currentIndex = index; // Set the selected index on click
                control.popup.close()
            }

        }
    }

    popup: Popup {
        width:          control.width
        topMargin:      0
        bottomMargin:   0

        contentItem: ListView {
            clip:                   true
            implicitHeight:         contentHeight
            model:                  control.delegateModel
            currentIndex:           control.highlightedIndex
            highlightMoveDuration:  400

            Rectangle {
//                z:              10
                width:          parent.width
                height:         parent.height
                color:          "transparent"
                border.color:   dcPallete.buttonBorder
            }
        }

        background: Rectangle {
            color: dcPallete.button
            border.color: dcPallete.buttonBorder
        }
    }


    background: Rectangle {
        color:          dcPallete.button
        border.color:   dcPallete.buttonBorder
        border.width:   1
    }



}

