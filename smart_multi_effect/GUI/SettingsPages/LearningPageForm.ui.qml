import QtQuick 2.12
import QtQuick.Controls 2.5

Item {
    id: element1
    width: 1024
    height: 500

    Rectangle {
        id: rectangle
        color: "#080a10"
        anchors.fill: parent
    }

    Image {
        id: image
        anchors.fill: parent
        fillMode: Image.PreserveAspectCrop
        source: "MenuBackground.png"
    }

    Text {
        id: element
        x: 444
        width: 463
        height: 88
        color: "#f4f1f1"
        text: qsTr("training")
        anchors.top: parent.top
        anchors.topMargin: 50
        anchors.horizontalCenter: parent.horizontalCenter
        styleColor: "#f4f1f1"
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        font.pixelSize: 50
    }

    Text {
        id: repeatsLabel
        objectName: "repeatsLabel"
        y: 0
        width: 377
        height: 61
        color: "#f4f1f1"
        text: qsTr("repeats: ")
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignLeft
        font.pixelSize: 50
        styleColor: "#f4f1f1"
    }

    BusyIndicator {
        id: busyIndicator
        objectName: "busyIndicator"
        x: 831
        y: 308
        spacing: 0
        scale: 1
    }
}
