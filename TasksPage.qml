import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.3

Page {
    id: root
    signal buttonClicked();

    anchors.fill: stackView
    background: Rectangle{
        color: bgColor
    }
    header: PageHeader {
        id: pageHeader
        color:  bgColor

    }
    //contentItem:

    ListView {
        id: listView
        anchors.fill: parent
        spacing: defMargin

        model: taskModel
        delegate: Rectangle {
            height: 18 + (_textEdit.lineCount * 18) + 18
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.margins: defMargin * 2
            color: bubbleColor
            radius: 10

            Button {
                id: _button
                anchors.fill: parent
                background: Rectangle {
                    anchors.margins: defMargin * 2
                    radius: 10
                    color: {
                        if(index === currentIndex)
                            parent.pressed ? Qt.darker(bubbleColor) :
                            parent.hovered ? Qt.lighter(bubbleColor) :
                            Qt.lighter(bubbleColor)

                        else
                            parent.pressed ? Qt.darker(bubbleColor) :
                            parent.hovered ? Qt.lighter(bubbleColor) :
                            bubbleColor
                    }

                }
                onClicked: {
                    if(currentIndex === index)
                        currentIndex = -1
                    else
                        currentIndex = index
                }

                onDoubleClicked: {
                    currentIndex = -1
                    taskModel.removeTask(index)
                }

            }
            MouseArea{
                anchors.fill: parent
                onClicked: _button.clicked()
                onDoubleClicked: _dialog.open()
            }

            Text {
                id: _textEdit

                anchors.left: parent.left
                anchors.top: parent.top
                anchors.right: _progress.left
                anchors.bottom: _time.top
                anchors.margins: defMargin / 2

                text: model.text

                font.pixelSize: 18
                font.bold: true

                wrapMode: Text.WordWrap
            }
            Text {
                id: _time
                anchors.right: parent.right
                anchors.bottom: parent.bottom
                anchors.margins: defMargin / 2
                anchors.topMargin: defMargin
                text: model.time
                font.pixelSize: 12
                font.bold: true
                color: "yellow"
            }

            Text {
                id: _progress
                anchors.right: parent.right
                anchors.top: parent.top

                anchors.margins: defMargin / 2
                text: model.progress
                font.pixelSize: 12
                font.bold: true
                color: "green"
            }
            Rectangle {
                id: _rectDialog

                anchors.fill: parent

                anchors.margins: defMargin
                width: listView.width
                height: listView.height
                z: -1

                Dialog {
                    id: _dialog
                    width: parent.width

                    background: Rectangle{
                        color: Qt.lighter(bgColor)
                    }

                    header:
                        Label{
                        text:  "Delete a task?"
                        font.pixelSize: 18
                        font.bold: true
                        color: "Red"
                        horizontalAlignment: Text.AlignHCenter

                    }

                    contentItem:
                        Label{
                        text:  qsTr("Are you sure?")
                        font.pixelSize: 18
                        font.bold: true
                        color: "Blue"
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                    }

                    footer:
                        DialogButtonBox {
                        standardButtons: Dialog.Yes | Dialog.Cancel

                        background: Rectangle{
                            color: Qt.lighter(bgColor)
                        }
                    }

                    onAccepted: {
                        _button.doubleClicked();
                    }
                    onRejected: {
                    }
                }
            }
        }    
    }
    footer:
        PageFooter {
        leftButtonName: "Exit"        
        onLeftButtonClicked: {
            close();
        }
        rightButtonName: currentIndex === -1 ? "AddTask" : "Change"
        rightButtonColor: currentIndex === -1 ? "Green" : "Yellow"
        onRightButtonClicked: {
            root.buttonClicked(currentIndex);
        }
    }
}
