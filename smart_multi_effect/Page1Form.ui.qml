import QtQuick 2.12
import QtQuick.Controls 2.5

Page {
    width: 1024
    height: 550

    title: qsTr("Page 1")

    Label {
        text: qsTr("You are on Page 1.")
        anchors.verticalCenterOffset: -290
        anchors.horizontalCenterOffset: -451
        anchors.centerIn: parent
    }
}
