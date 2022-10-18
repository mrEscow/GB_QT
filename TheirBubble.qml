import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import EscowCompany 1.0
import QtQuick.Layouts 1.3

Component {
    Rectangle {
        height: 10 + textPixelSize + ((text.lineCount+1) * textPixelSize) + textPixelSize
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.margins: defMargin * 2
        anchors{
            left: parent.left
            right: parent.right
            margins: defMargin * 2
            rightMargin: parent.width / 3
        }

        color: bubbleColor
        radius: 10

        Text {
            id: name
            anchors {
                left: parent.left
                top: parent.top
                margins: defMargin
            }

            text: model.name
            font.pixelSize: 16
            font.bold: true
        }
        Text {
            id: text
            anchors {
                top: name.bottom
                left: parent.left
                right: parent.right
                bottom: time.top
                leftMargin: defMargin * 2
                rightMargin: defMargin
            }
            text: model.text
            font.pixelSize: 16
            font.bold: true
            wrapMode: Text.WordWrap
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
