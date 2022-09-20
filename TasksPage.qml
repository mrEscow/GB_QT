import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.3

Page {
    id: root
    signal buttonClicked();
    anchors.fill: stackView
    background: Rectangle{
        color: bgColor
    }
    header: PageHeader {
        id: pageHeader
        color:  bgColor

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
                text: model.task
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

            Text {
                anchors.right: parent.right
                anchors.top: parent.top
                anchors.margins: defMargin / 2
                text: model.prog
                font.pixelSize: 16
                font.bold: true
                color: "green"
            }
        }
    }
    footer:
        PageFooter {
        leftButtonName: "Exit"
        onLeftButtonClicked: {
            close();
        }
        rightButtonName: "AddTask"
        onRightButtonClicked: {
            root.buttonClicked();
        }
    }
}
