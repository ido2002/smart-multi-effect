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

        Image {
            id: image
            x: -140
            y: -54
            anchors.leftMargin: -171
            anchors.topMargin: -54
            anchors.rightMargin: -157
            anchors.bottomMargin: -76
            anchors.fill: parent
            source: "PresetBackground.png"
            fillMode: Image.PreserveAspectFit

            Item {
                id: element1
                objectName: "effect_1"
                width: 280
                height: 160
                anchors.top: parent.top
                anchors.topMargin: 185
                anchors.left: parent.left
                anchors.leftMargin: 200
            }

            Item {
                id: element2
                objectName: "effect_2"
                x: 200
                y: 80
                width: 280
                height: 160
                anchors.horizontalCenterOffset: 0
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 285
            }

            Item {
                id: element3
                objectName: "effect_3"
                x: 872
                y: 185
                width: 280
                height: 160
                anchors.bottom: parent.bottom
                anchors.rightMargin: 200
                anchors.right: parent.right
                anchors.bottomMargin: 285
            }

            Item {
                id: element4
                objectName: "effect_4"
                x: 8
                y: 185
                width: 280
                height: 160
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 105
                anchors.leftMargin: 200
                anchors.left: parent.left
            }

            Item {
                id: element5
                objectName: "effect_5"
                x: 200
                y: 365
                width: 280
                height: 160
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 105
            }

            Item {
                id: element6
                objectName: "effect_6"
                x: 872
                y: 365
                width: 280
                height: 160
                anchors.right: parent.right
                anchors.rightMargin: 200
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 105
            }


        }

        Text {
            id: headLine
            objectName: "presetHeadline"
            x: 0
            y: 42
            width: 1024
            height: 80
            color: "#efeeee"
            text: qsTr("rock: acdc")
            font.bold: true
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 59
        }



    }
}

/*##^##
Designer {
    D{i:3;anchors_x:200;anchors_y:185}D{i:4;anchors_height:160;anchors_x:200;anchors_y:185}
D{i:5;anchors_height:160;anchors_x:200;anchors_y:185}D{i:6;anchors_height:160;anchors_x:200;anchors_y:185}
D{i:7;anchors_height:160;anchors_x:200;anchors_y:185}D{i:8;anchors_height:160;anchors_x:200;anchors_y:185}
}
##^##*/
