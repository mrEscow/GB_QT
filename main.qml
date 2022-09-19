import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.3

Window {
    id: rootWin
    visible: true
    width: 640
    height: 480
    title: qsTr("ToDoList")

    readonly property int defMargin: 10
    readonly property color panelColor: "#17212B"
    readonly property color bubbleColor: "#2b5278"
    readonly property color bgColor: "#0E1621"
    readonly property color textColor: "white"

    Page {
        id: page
        anchors.fill: parent

        header: PageHeader {
        }
        footer: MessageEditor{
            onNewMessage: {
                var newMsg = {};
                newMsg.text = msg;
                newMsg.time = Qt.formatDate(new Date(),"dd.mm.yyyy")
                listModel.append(newMsg);
            }
        }
        background: Rectangle{
            color: bgColor
        }

        ListView {
            id: listView
            anchors.fill: parent
            spacing: defMargin

            model: listModel
            delegate: Rectangle {
                height: 60
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.margins: defMargin * 2
                color: "lightgray"
                radius: 10

                Text {
                    anchors.fill: parent
                    anchors.margins: defMargin
                    text: model.text
                    font.pixelSize: 20
                    font.bold: true
                }
                Text {
                    anchors.right: parent.right
                    anchors.bottom: parent.bottom
                    anchors.margins: defMargin / 2
                    text: model.time
                    font.pixelSize: 12
                    font.bold: true
                }
            }
        }
        ListModel {
            id: listModel
            ListElement {
                text: "Писать код"
                time: "dd.mm.yyyy"
            }
            ListElement {
                text: "Писать код!"
                time: "dd.mm.yyyy"
            }
            ListElement {
                text: "Писать код!!!"
                time: "dd.mm.yyyy"
            }
            ListElement {
                text: "Писать код!!!!!"
                time: "dd.mm.yyyy"
            }
        }
    }

//    MessageEditor {
//        id: buttonsLayout
//    }
}

