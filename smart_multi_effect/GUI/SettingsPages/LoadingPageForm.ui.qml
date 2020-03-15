import QtQuick 2.12
import QtQuick.Controls 2.5

Item {
    width: 1024
    height: 500


    Rectangle {
        id: rectangle
        color: "#191919"
        anchors.fill: parent
    }
    Image {
        id: image
        anchors.fill: parent
        fillMode: Image.PreserveAspectCrop
        source: "MenuBackground.png"

        BusyIndicator {
            id: busyIndicator
            x: 356
            y: 172
            width: 313
            height: 257
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            wheelEnabled: false
        }
    }
}
