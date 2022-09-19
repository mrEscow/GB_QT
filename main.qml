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

    Page {
        id: page
        anchors.fill: parent

        ListView {
            id: listView
            anchors.fill: parent

            model: ["aaaa", "bbbb", "cccc", "dddd"]
            delegate: Rectangle {
                height: 60
                width: ListView.view.width
                border.color: "black"
                border.width: 3
                color: "lightgray"

                Text {
                    anchors.centerIn: parent
                    text: modelData
                    font.pixelSize: 20
                    font.bold: true
                }
            }
        }
    }

    ColumnLayout {
        id: buttonsLayout
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        anchors.margins: 15

        Button {
            id: button_text
            text: qsTr("Add Text")
            font.pixelSize: 20
            font.bold: true
            background: ButtonStyle {}
            onClicked: {
                textEdit.append("\nAdding text\n")
            }
        }
        Button {
            id: button_color
            text: qsTr("Change Color")
            font.pixelSize: 20
            font.bold: true
            background: ButtonStyle {}
            onClicked: {
                rootWin.color = Qt.rgba(Math.random(), Math.random(), Math.random())

            }
        }
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
}

