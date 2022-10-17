import QtQuick 2.15
import QtQuick.Controls 2.15

Rectangle {
    id: root

    width: 480
    height: 640

    Component.onCompleted: {
        _listView.model.append({});
        _listView.model.append({});
        _listView.model.append({});
        _listView.model.append({});
        _listView.model.append({});
        _listView.model.append({});
        _listView.model.append({});
    }

    ListView {
        id: _listView
        anchors.fill: parent
        anchors.margins: 20

        model: ListModel {}
        spacing: 10

        delegate: Rectangle {
            width: parent.width
            height: 100
            color: "green"
        }
    }



}
