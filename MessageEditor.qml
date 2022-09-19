import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.3

RowLayout {
    id: buttonsLayout
    //anchors.bottom: parent.bottom
    anchors.right: parent.right
    anchors.left: parent.left
    //anchors.margins: 15

    Button {
        id: button_text
        text: qsTr("Add Text")
        font.pixelSize: 20
        font.bold: true
        background: ButtonStyle {}
        onClicked: {
            //textEdit.append("\nAdding text\n")
            listModel.append("ListElement")
        }
    }
//    Button {
//        id: button_color
//        text: qsTr("Change Color")
//        font.pixelSize: 20
//        font.bold: true
//        background: ButtonStyle {}
//        onClicked: {
//            rootWin.color = Qt.rgba(Math.random(), Math.random(), Math.random())

//        }
//    }
    Button {
        id: button_exit
        text: qsTr("Exit")
        font.pixelSize: 20
        font.bold: true
        background: ButtonStyle {}
        onClicked: {
            close()
        }
    }
}
