import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.3

Rectangle{
    anchors.fill: parent
    signal newMessage(string msg)
    anchors.margins: defMargin
    ColumnLayout {
        anchors.fill: parent
        Rectangle {
            color: bgColor
            //implicitWidth: 200
            implicitHeight: 30
            anchors.margins: defMargin
            Layout.alignment: Qt.AlignTop
            Text {
                text: "NewTask:"
                color: "blue"
                font.pixelSize: 15
                font.bold: true
                anchors.fill: parent
                anchors.margins: defMargin

            }
        }
        Rectangle {
            color: panelColor
            anchors.left: parent.left
            anchors.right: parent.right
            implicitWidth: 500
            implicitHeight: 75
            radius: 5
            Layout.alignment: Qt.AlignTop
            TextEdit{
                id: textEdit
                anchors.fill: parent
                anchors.margins: defMargin
                font.pixelSize: 20
                font.bold: true
            }
        }
        //--------------------------------------------------------
        Rectangle {
            color: bgColor
            //implicitWidth: 200
            implicitHeight: 30
            anchors.margins: defMargin
            Layout.alignment: Qt.AlignTop
            Text {
                text: "Data:"
                color: "blue"
                font.pixelSize: 15
                font.bold: true
                anchors.fill: parent
                anchors.margins: defMargin

            }
        }
        Rectangle {
            color: panelColor
            anchors.left: parent.left
            anchors.right: parent.right
            implicitWidth: 500
            implicitHeight: 75
            radius: 5
            Layout.alignment: Qt.AlignTop
            TextEdit{
                id: textEdit2
                anchors.fill: parent
                anchors.margins: defMargin
                font.pixelSize: 20
                font.bold: true
            }
        }
        //--------------------------------------------------------
        Rectangle {
            color: bgColor
            //implicitWidth: 200
            implicitHeight: 30
            anchors.margins: defMargin
            Layout.alignment: Qt.AlignTop
            Text {
                text: "Prioritet:"
                color: "blue"
                font.pixelSize: 15
                font.bold: true
                anchors.fill: parent
                anchors.margins: defMargin

            }
        }
        Rectangle {
            color: panelColor
            anchors.left: parent.left
            anchors.right: parent.right
            implicitWidth: 500
            implicitHeight: 75
            radius: 5
            Layout.alignment: Qt.AlignTop
            TextEdit{
                id: textEdit3
                anchors.fill: parent
                anchors.margins: defMargin
                font.pixelSize: 20
                font.bold: true
            }
        }
        //--------------------------------------------------------
        RowLayout {

            anchors.right: parent.right
            anchors.bottom: parent.bottom
//            implicitWidth: 200
//            implicitHeight: 75
            anchors.margins: defMargin * 2
            Button {
                id: button
                text: qsTr("Add Task")
                font.pixelSize: 18
                font.bold: true
                background: ButtonStyle {}
                Layout.alignment: Qt.AlignRight
                onClicked: {
                    if(textEdit.text !== ""){
                        newMessage(textEdit.text)
                        textEdit.clear()
                    }
                }
            }
        }
    }
}
