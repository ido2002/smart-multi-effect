import QtQuick 2.12
import QtQuick.Controls 2.5

Item {
    id: element
    width: 350
    height: 200

    Frame {
        id: frame
        anchors.fill: parent

        Rectangle {
            id: rectangle
            x: -12
            y: -12
            width: 350
            height: 200
            color: "#032b0b"
        }

        Label {
            id: label
            objectName: "effectNameLable"
            x: 5
            y: 119
            text: qsTr("Effect Name")
            font.pixelSize: 40
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            wrapMode: Text.NoWrap
        }

        Switch {
            objectName: "switch"
            id: element1
            x: 132
            y: 119
            anchors.horizontalCenterOffset: 125
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 9
            scale: 1.6
        }

        EffectDialForm {
            objectName: "dial3"
            id: effectDialForm
            scale: 0.8
            anchors.top: parent.top
            anchors.topMargin: -23
            anchors.left: parent.left
            anchors.leftMargin: -27
        }

        EffectDialForm {
            objectName: "dial1"
            id: effectDialForm2
            x: 203
            y: 132
            scale: 0.8
            anchors.top: parent.top
            anchors.topMargin: -23
            anchors.right: parent.right
            anchors.rightMargin: -27
        }

        EffectDialForm {
            objectName: "dial2"
            id: effectDialForm1
            x: 76
            anchors.horizontalCenterOffset: 1
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
