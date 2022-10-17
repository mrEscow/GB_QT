import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import EscowCompany 1.0

Rectangle {
    id: root
    width: 480
    height: 640
    visible: true
    color: "#e5ecef"

    ChatClient {
        id: chatClient
    }

    property string login: "login"
    property string password: "password"

    // Javascript-функция для проверки данных
    function checkCredentials() {
        if (chatClient.checkCredentials(loginTextField.text, passwordTextField.text))
            console.log("Удачный вход")
        else
            failAnimation.start();
    }

    Rectangle {
        id: credentials
        color: "white"
        anchors.centerIn: parent
        radius: 5
        width: 300
        height: 250
        property string textColor: "#535353"

        Column { // аналог QVBoxLayout
            anchors.fill: parent // объект занимает все пространство родителя
            padding: 32 // отступы по 4 сторонам от родительского элемента
            spacing: 32 // отступы между элементами
            TextField {
                id: loginTextField
                anchors.horizontalCenter: parent.horizontalCenter
                placeholderText: qsTr("Логин")
                color: credentials.textColor
                // onEnterPressed и onReturnPressed – две кнопки Enter на стандартной клавиатуре
                Keys.onEnterPressed: checkCredentials()
                Keys.onReturnPressed: checkCredentials()

            }
            TextField {
                id: passwordTextField
                echoMode: TextInput.Password // звездочки вместо пароля
                anchors.horizontalCenter: parent.horizontalCenter
                placeholderText: qsTr("Пароль")
                color: credentials.textColor
                Keys.onEnterPressed: checkCredentials()
                Keys.onReturnPressed: checkCredentials()
            }
            Button {
                id: submitButton
                width: 200
                height: 40
                background: Rectangle {
                    color: parent.down ? "#bbbbbb" :
                    (parent.hovered ? "#d6d6d6" : "#f6f6f6")
                }
                text: qsTr("Вход")
                anchors.horizontalCenter: parent.horizontalCenter
                onClicked: checkCredentials()
            }
        }
    }

    // анимации внутри ParallelAnimation будут выполнены параллельно
    ParallelAnimation{
        id: failAnimation
        SequentialAnimation {
            // Группа анимаций внутри SequentialAnimation будет выполнена последовательно
            PropertyAnimation {
                // Текст внутри полей логина и пароля моментально изменит цвет на темно-красный
                targets: [loginTextField, passwordTextField]
                property: "color"
                to: "dark red"
                duration: 0
            }
            PropertyAnimation {
                // После этого за 400 миллисекунд вернется к обычному цвету
                targets: [loginTextField, passwordTextField]
                property: "color"
                to: credentials.textColor
                duration: 400
            }
        }
        SequentialAnimation {
            // Подложка secondaryFrame сместится на -5 пикселей относительно
            // центра, затем передвинется на позицию +5, а потом вернётся в исходное положение.
            // Произойдет “потрясывание” формы.
            NumberAnimation { target: credentials; property:
                "anchors.horizontalCenterOffset"; to: -5; duration: 50 }
            NumberAnimation { target: credentials; property:
                "anchors.horizontalCenterOffset"; to: 5; duration: 100 }
            NumberAnimation { target: credentials; property:
                "anchors.horizontalCenterOffset"; to: 0; duration: 50 }
        }
    }
}

