import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.3

Window {
    id: rootWin
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    Rectangle{
        TextEdit {
            width: 240
            text: "<b>Hello</b> <i>World!</i>"
            font.family: "Helvetica"
            font.pointSize: 14
            color: "blue"
            focus: true
            id:textEdit
        }
    }
    ColumnLayout{
        id: buttonsLayout
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        anchors.margins: 15

        Button{
            text: qsTr("Add Text")
            onClicked: {
                textEdit.append("\nAdding text\n")
            }
        }
        Button{
            text: qsTr("Change Color")

            onClicked: {
                rootWin.color = Qt.rgba(Math.random(), Math.random(), Math.random())

            }
        }
        Button{
            text: qsTr("Exit")

            onClicked: {
                close()
            }
        }
    }

    Rectangle{
        anchors.fill: buttonsLayout
        border.color: "black"
        border.width: 5
        color: "transparent"
    }
}

