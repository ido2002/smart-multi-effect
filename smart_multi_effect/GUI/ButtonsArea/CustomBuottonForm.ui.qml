import QtQuick 2.12

Item {
    width: 192
    height: 80
    opacity: 1

    Rectangle {
        objectName: "button"
        id: rectangle
        x: 0
        y: 0
        width: 192
        height: 80
        color: "#1e222e"
        anchors.fill: parent



        Text {
            id: element
            objectName: "buttonText"
            x: 80
            y: 71
            width: 260
            height: 108
            color: "#faf9f9"
            text: qsTr("Text")
            font.family: "Verdana"
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
            font.pixelSize: 45
        }
    }
}
