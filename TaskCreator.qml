import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.3

Page {
    id: root
    signal buttonClicked();
    signal errorTask();
    property string  date: {
        if(currentIndex === -1)
            Qt.formatDate(new Date(),"dd.MM.yyyy")
        else
            Qt.formatDate(taskModel.currentTime(currentIndex),"dd.MM.yyyy")
    }
    anchors.fill: stackView
    background: Rectangle{
        color: bgColor
    }
    header: PageHeader {
        id: pageHeader
        color:  bgColor
    }
    MessageEditor{
        id: msgEditor

        textEdit.text: {
            if(currentIndex !== -1)
                taskModel.currentText(currentIndex)
            else
                ""
        }
        slider.value: {
            if(currentIndex !== -1)
                taskModel.currentProgress(currentIndex);
            else
                0
        }
        anchors.fill: parent
        color:  bgColor
    }
    footer:
        PageFooter {
        leftButtonName: "Back"
        onLeftButtonClicked: {
            currentIndex = -1;
            root.buttonClicked();
        }
        rightButtonName: currentIndex === -1 ? "AddTask" : "Change"
        rightButtonColor: currentIndex === -1 ? "Green" : "Yellow"

        onRightButtonClicked: {
            if(msgEditor.textEdit.text === ""){
                msgEditor.rect.border.color = "red"
                return
            }
            msgEditor.rect.border.color = "transporent"

            var newMsg = {};
            newMsg.task = msgEditor.textEdit.text;           
            newMsg.time = date;
            newMsg.prog = msgEditor.slider.value.toString();

            if(currentIndex === -1)
                taskModel.append(newMsg.task,newMsg.time,newMsg.prog);
            else
                taskModel.updateTask(currentIndex, newMsg.task,newMsg.time,newMsg.prog)

            msgEditor.textEdit.clear();
            currentIndex = -1;
            root.buttonClicked();
        }
    }
}
