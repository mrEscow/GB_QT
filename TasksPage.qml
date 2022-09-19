import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.3

Page {
    id: root
    signal buttonClicked();
    anchors.fill: parent
    background: Rectangle{
        color: bgColor
    }
    header: PageHeader {
        id: pageHeader
        color:  bgColor

    }
//    footer: MessageEditor{
//        id: pageFooter
//        color:  bgColor

//        onNewMessage: {
//            var newMsg = {};
//            newMsg.text = msg;
//            newMsg.time = Qt.formatDate(new Date(),"dd.MM.yyyy")
//            listModel.append(newMsg);
//        }
//    }
    footer: RowLayout {
        Button {
            id: button
            text: qsTr("Add Task")
            font.pixelSize: 18
            font.bold: true
            background: ButtonStyle {}
            Layout.alignment: Qt.AlignRight
            onClicked: {
    //            if(textEdit.text !== ""){
    //                newMessage(textEdit.text)
    //                textEdit.clear()
    //            }
                root.buttonClicked();
            }
        }
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
            color: bubbleColor
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

}
