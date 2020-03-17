import QtQuick 2.4

Item {
    id: element
    width: 1024
    height: 500

    Image {
        id: image1
        objectName: "navigationButton_Right"
        x: 654
        y: 236
        source: "triangleButton.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: image2
        objectName: "navigationButton_Left"
        x: 313
        y: 236
        rotation: 180
        source: "triangleButton.png"
        fillMode: Image.PreserveAspectFit
    }

    Rectangle {
        id: rectangle
        x: 0
        y: 0
        width: 1024
        height: 500
        color: "#080a10"
    }

    Image {
        id: image
        scale: 1
        anchors.rightMargin: 0
        anchors.fill: parent
        source: "SongBackground.png"
        fillMode: Image.PreserveAspectCrop
    }

    Text {
        id: element1
        objectName: "SongText"
        x: 361
        y: 236
        width: 302
        height: 127
        color: "#efeeee"
        text: qsTr("")
        font.bold: true
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        font.pixelSize: 59
    }

    Text {
        id: element2
        x: 360
        y: 42
        width: 302
        height: 80
        color: "#efeeee"
        text: qsTr("Auto Switching")
        font.bold: true
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        font.pixelSize: 59
    }


}
