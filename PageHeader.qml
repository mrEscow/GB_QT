import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import EscowCompany 1.0
import QtQuick.Layouts 1.3

Rectangle {
    width: parent.height
    height: 60
    Text {
        anchors {
            horizontalCenter: parent.horizontalCenter
            verticalCenter: parent.verticalCenter
            margins: defMargin
        }

        text: qsTr("Chatik")
        font.pixelSize: 40
        font.bold: true
        color: "red"
    }
}
