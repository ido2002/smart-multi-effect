import QtQuick 2.4

Item {
    id: element
    width: 250
    height: 250
    objectName:SongFrame

    BorderImage {
        id: borderImage
        objectName: "SongFrameImage"
        x: 18
        y: 32
        width: 250
        height: 200
        anchors.verticalCenterOffset: -25
        anchors.horizontalCenterOffset: 0
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        source: "qrc:/qtquickplugin/images/template_image.png"
    }

    Text {
        id: element1
        objectName: "songFrameText"
        x: 93
        y: 200
        width: 250
        height: 50
        text: qsTr("Text")
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        anchors.horizontalCenter: parent.horizontalCenter
        font.pixelSize: 40
    }
}
