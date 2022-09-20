import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.3

Window {
    id: rootWin
    visible: true
    width: 300
    height: 550
    title: qsTr("ToDoList")
    readonly property int defMargin: 10
    readonly property color panelColor: "#17212B"
    readonly property color bubbleColor: "#2b5278"
    readonly property color bgColor: "#0E1621"
    readonly property color textColor: "white"
    ListModel {
        id: listModel
    }
    StackView {
        id: stackView
        anchors.fill: parent
        initialItem: pageTask
    }
    TasksPage {
        id: pageTask
        visible: false
        onButtonClicked: {
            stackView.push(taskCreator);
        }
    }
    TaskCreator {
        id: taskCreator
        visible: false
        onButtonClicked: {
            stackView.pop(pageTask);
        }
    }
    Component.onCompleted: {
        var coreDates = appCore.getDates();
        for(var i = 0; i < coreDates.length;){
            var msg = {};
            msg.task = coreDates[i++];
            msg.time = coreDates[i++];
            msg.prog = coreDates[i++];
            listModel.append(msg);
        }
    }
}


