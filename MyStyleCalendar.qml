import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.3


Rectangle {

    property alias currentDate: calendar.selectedDate
    color: panelColor
    Layout.fillWidth: true
    Layout.fillHeight: true
    implicitHeight: 3
    radius: 5
    Layout.alignment: Qt.AlignCenter


    Calendar {
        id: calendar
        anchors.fill: parent
        style: CalendarStyle {
            background: Rectangle{
                color:  panelColor
                border.color: panelColor
            }

            gridVisible: false
            dayOfWeekDelegate: Rectangle {
                color: panelColor
                height: 10
                Label {
                    text: control.locale.dayName(styleData.dayOfWeek, control.dayOfWeekFormat)
                    anchors.centerIn: parent
                    color: "yellow"
                }
            }
            navigationBar: Rectangle {
            height: 15
            color: panelColor

            Rectangle {
                color: panelColor
                height: 1
                width: parent.width
            }

            Rectangle {
                color: panelColor
                anchors.bottom: parent.bottom
                height: 1
                width: parent.width
            }

            Button {
                id: previousMonth
                width: parent.height
                height: width
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                text: "<"
                onClicked: control.showPreviousMonth()
                font.bold: true
                font.pixelSize: 16

                background: Rectangle{
                    color:  panelColor
                }

            }
            Label {
                id: dateText
                text: styleData.title
                elide: Text.ElideRight
                horizontalAlignment: Text.AlignHCenter
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: previousMonth.right
                anchors.leftMargin: 2
                anchors.right: nextMonth.left
                anchors.rightMargin: 2
                color: "yellow"
                font.bold: true
            }
            Button {
                id: nextMonth
                width: parent.height
                height: width
                anchors.verticalCenter: parent.verticalCenter
                anchors.right: parent.right
                text: ">"
                onClicked: control.showNextMonth()
                font.bold: true
                font.pixelSize: 16
                background: Rectangle{
                    color:  panelColor

                }

            }
          }
            dayDelegate: Rectangle {

                    color:  panelColor

                         gradient: Gradient {
                             GradientStop {
                                 position: 0.00
                                 color: styleData.selected ? "#111" : (styleData.visibleMonth && styleData.valid ? "#444" : "#666");
                             }
                             GradientStop {
                                 position: 1.00
                                 color: styleData.selected ? "#444" : (styleData.visibleMonth && styleData.valid ? "#111" : "#666");
                             }
                             GradientStop {
                                 position: 1.00
                                 color: styleData.selected ? "#777" : (styleData.visibleMonth && styleData.valid ? "#111" : "#666");
                             }
                         }

                         Label {
                             text: styleData.date.getDate()
                             anchors.centerIn: parent
                             color: styleData.valid ? "yellow" : "grey"
                         }

                         Rectangle {
                             width: parent.width
                             height: 1
                             color: "#555"
                             anchors.bottom: parent.bottom
                         }

                         Rectangle {
                             width: 1
                             height: parent.height
                             color: "#555"
                             anchors.right: parent.right
                         }
                     }
                }

    }
}
