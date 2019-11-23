import QtQuick 2.12
import QtQuick.Controls 2.5

Page {
    width: 1024
    height: 550

    title: qsTr("Page 2")

    Label {
        text: qsTr("You are on Page 2.")
        anchors.verticalCenterOffset: 0
        anchors.horizontalCenterOffset: 1
        anchors.centerIn: parent
    }
}
