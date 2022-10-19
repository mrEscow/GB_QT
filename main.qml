import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import EscowCompany 1.0

ApplicationWindow {
    id: root
    width: 480
    height: 640
    visible: true

    // Style
    readonly property int defMargin: 10
    // StyleColors
    readonly property color bgColor: "#e5ecef"
    readonly property color bgColorChat: "#0E1621"
    readonly property color panelColor: "#17212B"
    readonly property color bubbleColor: "#2b5278"

    readonly property color textColor: "white"

    ListModel{ id: listModel }

    ChatClient { id: chatClient }

    Connections {
        target: chatClient
        onMessageFromServer: {
            console.log("Новое сообщение!")

            console.log(who)
            console.log(name)
            console.log(text)
            console.log(time)

            listModel.append({
                who: who,
                name: name,
                text: text,
                time: time
            });
        }

        onConectToChat:{
            stackView.push(chatPage)
        }
    }

    StackView{
        id: stackView
        anchors.fill: parent
        initialItem: startingPage
        //initialItem: chatPage
    }

    StartingPage {
        id: startingPage
        visible: false
    }

    ChatPage {
        id: chatPage
        visible: false
    }
}

