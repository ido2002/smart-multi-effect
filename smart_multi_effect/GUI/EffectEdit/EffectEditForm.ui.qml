import QtQuick 2.12
import QtQuick.Controls 2.5

Item {
    id: element
    width: 280
    height: 160

    Frame {
        id: frame
        anchors.fill: parent

        Rectangle {
            id: rectangle
            objectName: "rect"
            x: -12
            y: -12
            width: 280
            height: 160
            color: "#032b0b"
        }

        Label {
            id: label
            objectName: "effectNameLable"
            y: 102
            width: 258
            height: 51
            text: qsTr("Effect Name")
            anchors.bottom: parent.bottom
            anchors.bottomMargin: -17
            anchors.left: parent.left
            anchors.leftMargin: -28
            scale: 0.8
            font.pixelSize: 40
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignLeft
            wrapMode: Text.NoWrap
        }

        Switch {
            objectName: "switch"
            id: element1
            x: 200
            y: 115
            width: 62
            height: 30
            anchors.right: parent.right
            anchors.rightMargin: -6
            anchors.bottom: parent.bottom
            anchors.bottomMargin: -9
            scale: 1.2
        }

        EffectDialForm {
            objectName: "dial3"
            id: effectDialForm
            scale: 0.8
            anchors.top: parent.top
            anchors.topMargin: -23
            anchors.left: parent.left
            anchors.leftMargin: -40
        }

        EffectDialForm {
            objectName: "dial1"
            id: effectDialForm2
            x: 144
            y: 132
            scale: 0.8
            anchors.top: parent.top
            anchors.topMargin: -23
            anchors.right: parent.right
            anchors.rightMargin: -40
        }

        EffectDialForm {
            objectName: "dial2"
            id: effectDialForm1
            x: 76
            anchors.horizontalCenterOffset: 0
            scale: 0.8
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top
            anchors.topMargin: -23
        }
    }
}

/*##^##
Designer {
    D{i:3;anchors_x:169}D{i:4;anchors_x:"-12";anchors_y:143}D{i:5;anchors_x:"-12";anchors_y:144}
D{i:6;anchors_y:"-12"}D{i:7;anchors_y:"-12"}D{i:1;anchors_height:200;anchors_width:200;anchors_x:0;anchors_y:0}
}
##^##*/

