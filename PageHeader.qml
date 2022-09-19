import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.3

RowLayout {
    anchors.top: parent.top
    anchors.margins: 5
    Text {
        text: qsTr("ToDoList:")
        font.pixelSize: 40
        font.bold: true
    }
    implicitWidth: 200
    implicitHeight: 100

}
