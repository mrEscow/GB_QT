import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.3

Rectangle {
    implicitWidth: 200
    implicitHeight: 80
    RowLayout {
        id: rlo
        anchors.fill: parent
        anchors.margins: defMargin
        Text {
            text: qsTr("(: ToDoList :)")
            font.pixelSize: 40
            font.bold: true
            color: "red"
            Layout.alignment: Qt.AlignCenter
        }
    }
}
