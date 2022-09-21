import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.3

Rectangle {
    id: root
    property string leftButtonName: "left"
    property string rightButtonName: "right"
    signal leftButtonClicked()
    signal rightButtonClicked()

    implicitWidth: 200
    implicitHeight: 80
    color: bgColor
    //border.color: "#ffffff"
    RowLayout {
        anchors.fill: parent
        anchors.margins: defMargin *2
        spacing: defMargin * 5
        Button {
            text: qsTr(leftButtonName)
            font.pixelSize: 18
            font.bold: true
            background: ButtonStyleGradient {}
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignLeft
            onClicked: {
                leftButtonClicked()
            }
        }
        Button {
            text: qsTr(rightButtonName)
            font.pixelSize: 18
            font.bold: true
            background: ButtonStyleGradient {}
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignRight
            onClicked: {
                rightButtonClicked()
            }
        }
    }
}
