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
            id: button_1
            text: qsTr("Add Text")
            background: ButtonStyle {}

            onClicked: {
                textEdit.append("\nAdding text\n")
            }
        }
        Button{
            id: testButton
            text: qsTr("Change Color")
            background: ButtonStyle {}
            onClicked: {
                rootWin.color = Qt.rgba(Math.random(), Math.random(), Math.random())

            }
        }
        Button{
            text: qsTr("Exit")
            background: ButtonStyle {}
            onClicked: {
                close()
            }
        }

//        Rectangle {
//            width: 100; height: 100
//            gradient: Gradient {
//                GradientStop { position: 0.0; color: "red" }
//                GradientStop { position: 0.33; color: "yellow" }
//                GradientStop { position: 1.0; color: "green" }
//            }
//        }
    }

//    Rectangle{
//        anchors.fill: buttonsLayout
//        border.color: "black"
//        border.width: 5
//        color: "transparent"
//    }
}

