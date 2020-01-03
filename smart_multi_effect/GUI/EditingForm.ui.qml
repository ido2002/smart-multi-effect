import QtQuick 2.12
import QtQuick.Controls 2.5

Page {
    id: page
    width: 1024
    height: 600

    title: qsTr("Edit Mode")

    Label {
        text: qsTr("You are on Page 2.")
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.top: parent.top
        anchors.topMargin: 0
    }
}
