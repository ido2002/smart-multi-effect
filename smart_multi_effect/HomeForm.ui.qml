import QtQuick 2.12
import QtQuick.Controls 2.5

Page {
    width: 1024
    height: 550

    title: qsTr("Home")

    Label {
        text: qsTr("You are on the home page.")
        anchors.centerIn: parent
    }
}
