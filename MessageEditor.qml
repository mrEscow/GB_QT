import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.3


Rectangle{
    property alias  textEdit: textEdit
    property alias slider: slider
    property Rectangle rect: rect

    anchors.fill: parent
    anchors.margins: defMargin
    ColumnLayout {
        id: columnLayout
        anchors.fill: parent
        Rectangle {
            color: bgColor
            Layout.fillWidth: true
            Layout.fillHeight: true
            implicitHeight: 1
            anchors.margins: defMargin
            Layout.alignment: Qt.AlignTop
            Text {
                text: "NewTask:"
                color: "blue"
                font.pixelSize: 15
                font.bold: true
                anchors.fill: parent
                anchors.margins: defMargin
                Layout.alignment: Qt.AlignTop
            }
        }
        Rectangle {
            id: rect
            color: panelColor
            Layout.fillWidth: true
            Layout.fillHeight: true
            implicitHeight: 2
            radius: 5
            Layout.alignment: Qt.AlignTop
            TextEdit{
                id: textEdit
                anchors.fill: parent
                anchors.margins: defMargin
                font.pixelSize: 20
                font.bold: true
                Layout.alignment: Qt.AlignTop
                color: "yellow"
            }
        }
        //--------------------------------------------------------
        Rectangle {
            color: bgColor
            Layout.fillWidth: true
            Layout.fillHeight: true
            implicitHeight: 1
            anchors.margins: defMargin
            Layout.alignment: Qt.AlignTop
            Text {
                text: "Data:"
                color: "blue"
                font.pixelSize: 15
                font.bold: true
                anchors.fill: parent
                anchors.margins: defMargin

            }
        }
        MyStyleCalendar {
            color: panelColor
        }

        //--------------------------------------------------------
        Rectangle {
            color: bgColor
            Layout.fillWidth: true
            Layout.fillHeight: true
            implicitHeight: 1
            anchors.margins: defMargin
            Layout.alignment: Qt.AlignTop
            Text {
                text: "Priority:"
                color: "blue"
                font.pixelSize: 15
                font.bold: true
                anchors.fill: parent
                anchors.margins: defMargin

            }
        }
        Rectangle {
            id: spliterRect
            color: panelColor
            Layout.fillWidth: true
            implicitHeight: 30
            radius: 5
            RowLayout {
                id: spliterLayout
                anchors.fill: parent
                Slider {
                    id: slider
                    from: 0
                    stepSize: 1
                    value: 10
                    to: 10
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                }
                Rectangle {
                    implicitWidth: 20
                    color: "transparent"
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    Text {
                        id: sliderValueText
                        anchors.centerIn: parent
                        font.pixelSize: 15
                        font.bold: true
                        text: slider.value
                        color: "yellow"
                    }
                }
            }
        }
        //--------------------------------------------------------
        Item {
            Layout.fillWidth: true
            Layout.fillHeight: true
            implicitHeight: 1
        }
        //--------------------------------------------------------
    }
}


