import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.3

Page {
    id: root
    signal buttonClicked();
    signal errorTask();
    property string  date: Qt.formatDate(new Date(),"dd.MM.yyyy")
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
        anchors.fill: parent
        color:  bgColor
    }
    footer:
        PageFooter {
        leftButtonName: "Back"
        onLeftButtonClicked: {
            root.buttonClicked();
        }
        rightButtonName: "AddTask"
        onRightButtonClicked: {
            if(msgEditor.textEdit.text === ""){
                msgEditor.rect.border.color = "red"
                return
            }
            msgEditor.rect.border.color = "transporent"

            var newMsg = {};
            newMsg.task = msgEditor.textEdit.text;
            msgEditor.textEdit.clear();
            newMsg.time = date;
            newMsg.prog = msgEditor.slider.value.toString();
            msgEditor.slider.value = 10;

            appCore.setDate(newMsg.task,newMsg.time,newMsg.prog);

            listModel.append(newMsg);
            root.buttonClicked();
        }
    }
}
