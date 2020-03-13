import QtQuick 2.4

Item {
    id: element
    width: 1024
    height: 500

    MouseArea {
        anchors.fill: parent
        enabled: true
        cursorShape: Qt.BlankCursor
    }

    Rectangle {
        id: rectangle
        x: 0
        y: 0
        width: 1024
        height: 500
        color: "#080a10"

        Image {
            id: image
            x: -140
            y: -54
            anchors.leftMargin: -140
            anchors.topMargin: -54
            anchors.rightMargin: -188
            anchors.bottomMargin: -76
            anchors.fill: parent
            source: "SongBackground.png"
            fillMode: Image.PreserveAspectFit
        }

        Item {
            id: element1
            objectName: "SongPreset"
            x: 512
            y: 170
            width: 250
            height: 250
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Text {
            id: element2
            x: 360
            y: 42
            width: 302
            height: 80
            color: "#efeeee"
            text: qsTr("Songs")
            font.bold: true
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 59
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

        Image {
            id: image1
            objectName: "navigationButton_Right"
            x: 654
            y: 236
            source: "triangleButton.png"
            fillMode: Image.PreserveAspectFit
        }
    }
}



