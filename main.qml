import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12

Window {
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
        text: qsTr("Add Text")
        onClicked: {
        textEdit.append("\nAdding text\n")
        }
    }
}

