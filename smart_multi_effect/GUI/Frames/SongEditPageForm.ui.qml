import QtQuick 2.4

Item {
    id: element
    width: 1024
    height: 500

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
        id: element2
        objectName: "headLine"
        x: 0
        y: 42
        width: 1024
        height: 80
        color: "#efeeee"
        text: qsTr("HeadLine")
        font.bold: true
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        font.pixelSize: 59
    }

    StyleEdit {
        id: styleEdit
        objectName: "styleEdit_1"
        x: 19
        y: 128
        anchors.horizontalCenter: parent.horizontalCenter
    }

    StyleEdit {
        id: styleEdit1
        objectName: "styleEdit_2"
        anchors.top: styleEdit.bottom
        anchors.topMargin: 20
        anchors.left: styleEdit.left
        anchors.leftMargin: 0
    }

    StyleEdit {
        id: styleEdit2
        objectName: "styleEdit_3"
        anchors.top: styleEdit1.bottom
        anchors.topMargin: 20
        anchors.left: styleEdit1.left
        anchors.leftMargin: 0
    }
}

/*##^##
Designer {
    D{i:4;anchors_x:19}D{i:5;anchors_x:19;anchors_y:258}D{i:6;anchors_x:19;anchors_y:258}
}
##^##*/

