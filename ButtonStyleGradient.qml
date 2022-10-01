import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.3

Rectangle {
    id: root
    color: "red"
    Gradient {
        id: normalGradient
        GradientStop { position: 0.0; color: "#252525" }
        GradientStop { position: 0.5; color: root.color}
        GradientStop { position: 1.0; color: "#252525" }
    }
    Gradient {
        id: hoveredGradient
        GradientStop { position: 0.0; color: "#252525" }
        GradientStop { position: 0.5; color: Qt.darker(root.color) }
        GradientStop { position: 1.0; color: "#252525" }
    }
    Gradient {
        id: pressedGradient
        GradientStop { position: 0.0; color: "#252525" }
        GradientStop { position: 0.5; color: Qt.lighter(root.color) }
        GradientStop { position: 1.0; color: "#252525" }
    }
    implicitWidth: 100
    implicitHeight: 50

    gradient: parent.pressed ? pressedGradient :
              parent.hovered ? hoveredGradient :
              normalGradient
    radius: 15
    border.width: 2.0
    border.color: "#000000"
}
