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
        text: qsTr("Recording Octaves")
        anchors.top: parent.top
        anchors.topMargin: 50
        anchors.horizontalCenter: parent.horizontalCenter
        styleColor: "#f4f1f1"
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        font.pixelSize: 50
    }

    Text {
        id: octaveLabel
        objectName: "octaveLabel"
        y: 0
        width: 291
        height: 325
        color: "#f4f1f1"
        text: qsTr("octave: low")
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 38
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        font.pixelSize: 50
        anchors.topMargin: 175
        styleColor: "#f4f1f1"
        anchors.top: parent.top
    }

    Text {
        id: octavesLabel
        objectName: "octavesLabel"
        x: 1
        y: 144
        width: 291
        height: 325
        color: "#f4f1f1"
        text: qsTr("octaves")
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        anchors.leftMargin: 336
        verticalAlignment: Text.AlignTop
        horizontalAlignment: Text.AlignHCenter
        font.pixelSize: 50
        anchors.topMargin: 0
        styleColor: "#f4f1f1"
        anchors.left: parent.left
        anchors.top: noteLabel.top
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

/*##^##
Designer {
    D{i:1;anchors_height:200;anchors_width:200;anchors_x:109;anchors_y:74}
}
##^##*/

