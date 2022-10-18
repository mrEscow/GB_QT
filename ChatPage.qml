import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import EscowCompany 1.0
import QtQuick.Layouts 1.3

Page {
    id : chatPage
    anchors.fill: stackView
    property int textPixelSize: 16

    Rectangle {
        id: bgRect
        anchors.fill: parent
        color: bgColor
    }

    header: PageHeader{
        id: pageHeader
         color:  bgColor
    }

    ListView {
        id: listView
        anchors.fill: parent
        spacing: defMargin

        model: listModel

        delegate: Loader {
            height: childrenRect.height
            width: parent.width
            sourceComponent: {
                switch(who) {
                case "ME" :
                    return myBubble;
                case "NotME":
                    return theirBubble;
                case "Server":
                    return serverBubble;
                }
            }
            MyBubble { id: myBubble }
            TheirBubble { id: theirBubble }
            ServerBubble { id: serverBubble }
        }
    }

    footer: Rectangle{
        width: parent.height
        height: 100
        color: bgColor
        anchors.margins: defMargin
        RowLayout {
            anchors.fill: parent
            anchors.margins: defMargin
            TextField {
                id: textInput
                Layout.fillWidth: true
                Keys.onEnterPressed: sendButton.clicked()
                Keys.onReturnPressed: sendButton.clicked()
            }
            Button {
                id: sendButton
                Layout.fillWidth: true
                text: "Отправить"
                onClicked: {
                    chatClient.sendMsg(textInput.text)
                    textInput.clear()
                }
            }
        }
    }
}
