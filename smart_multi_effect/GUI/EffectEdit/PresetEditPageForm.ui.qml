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

            EffectEdit {
                id: effectEdit
                x: 183
                y: 164
                scale: 0.8
            }

            EffectEdit {
                id: effectEdit1
                x: 183
                y: 345
                scale: 0.8
            }

            EffectEdit {
                id: effectEdit2
                x: 486
                y: 164
                scale: 0.8
            }

            EffectEdit {
                id: effectEdit3
                x: 486
                y: 345
                scale: 0.8
            }

            EffectEdit {
                id: effectEdit4
                x: 802
                y: 164
                scale: 0.8
            }

            EffectEdit {
                id: effectEdit5
                x: 802
                y: 345
                scale: 0.8
            }
        }

        Text {
            id: element2
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
