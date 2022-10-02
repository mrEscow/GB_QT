import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.3

Page {
    id: root

    property alias text: _msgEditor.textEdit
    property alias time: _msgEditor.calendar
    property alias progress: _msgEditor.slider

    signal buttonClicked();
    signal errorTask();

    anchors.fill: stackView
    background: Rectangle{
        color: bgColor
    }
    header: PageHeader {
        id: pageHeader
        color:  bgColor
    }
    MessageEditor{
        id: _msgEditor
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
            if(text === ""){
                _msgEditor.rect.border.color = "red"
                return
            }
            _msgEditor.rect.border.color = "transporent"

            var newMsg = {};
            newMsg.task = text.toString();
            newMsg.time = Qt.formatDate(new Date(time),"dd.MM.yyyy");
            newMsg.prog = progress.toString();

            if(currentIndex === -1)
                taskModel.append(newMsg.task,newMsg.time,newMsg.prog);
            else
                taskModel.updateTask(currentIndex, newMsg.task,newMsg.time,newMsg.prog)

            currentIndex = -1;
            root.buttonClicked();
        }
    }
}
