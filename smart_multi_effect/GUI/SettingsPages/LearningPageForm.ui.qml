import QtQuick 2.4

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
    }
}
