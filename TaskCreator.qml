import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.3

Page {
    id: root
    signal buttonClicked();
    anchors.fill: parent
    background: Rectangle{
        color: bgColor
    }
    header: PageHeader {
        id: pageHeader
        color:  bgColor

    }
    MessageEditor{
        anchors.fill: parent
        color:  bgColor

        onNewMessage: {
            var newMsg = {};
            newMsg.text = msg;
            newMsg.time = Qt.formatDate(new Date(),"dd.MM.yyyy")
            listModel.append(newMsg);
            root.buttonClicked();
        }
    }
}
