import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import EscowCompany 1.0
import QtQuick.Layouts 1.3

Component {
    Rectangle {
        height: 20 + textPixelSize + ((text.lineCount+1) * textPixelSize) + textPixelSize
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.margins: defMargin * 2
        anchors{
            left: parent.left
            right: parent.right
            margins: defMargin * 2
        }

        color: bubbleColor
        radius: 10

        Text {
            id: name
            anchors {
                top: parent.top
                horizontalCenter: parent.horizontalCenter
                verticalCenter: parent.verticalCenter
                margins: defMargin / 2
            }

            text: model.name
            font.pixelSize: 20
            font.bold: true
            color: "red"
        }
        Text {
            id: text
            anchors {
                //top: name.bottom
                horizontalCenter: parent.horizontalCenter
                verticalCenter: parent.verticalCenter
                //bottom: time.top
                //leftMargin: defMargin * 2
                ///rightMargin: defMargin
            }
            text: model.text
            font.pixelSize: 20
            font.bold: true
            wrapMode: Text.WordWrap
            color: "yellow"
        }

        Text {
            id: time
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            anchors.margins: defMargin / 2
            text: model.time
            font.pixelSize: 12
            font.bold: true
            color: "green"
        }

    }
}
