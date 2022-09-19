import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12

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
    Button{
        text: qsTr("Add Text And Change Color")

        anchors.bottom: parent.bottom
        anchors.right: parent.right
        anchors.margins: 15

        onClicked: {
            rootWin.color = Qt.rgba(Math.random(), Math.random(), Math.random())
            textEdit.append("\nAdding text\n")
        }
    }
}

