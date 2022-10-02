import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.3
import EscowCompany 1.0

Window {
    id: rootWin
    visible: true
    title: qsTr("ToDoList")
    width: 300
    height: 500

    readonly property int defMargin: 10
    readonly property color panelColor: "#17212B"
    readonly property color bubbleColor: "#2b5278"
    readonly property color bgColor: "#0E1621"
    readonly property color textColor: "white"

    property int currentIndex: -1;

    TaskModel {
        id: taskModel        
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
            rootWin.currentIndex = currentIndex;
            if(currentIndex !== -1){
                taskCreator.text = taskModel.currentText(currentIndex);
                taskCreator.time = new Date(Date.fromLocaleString(Qt.locale(), taskModel.currentTime(currentIndex), "dd.MM.yyyy"));
                taskCreator.progress = taskModel.currentProgress(currentIndex);
            }
            else {
                taskCreator.text = "";
                taskCreator.time = new Date();
                taskCreator.progress = 5;
            }


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
}


