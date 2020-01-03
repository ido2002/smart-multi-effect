import QtQuick 2.12
import QtQuick.Controls 2.5

Item {
    id: element
    width: 350
    height: 600

    Frame {
        id: frame
        anchors.fill: parent

        Rectangle {
            id: rectangle
            x: -12
            y: -12
            width: 350
            height: 600
            color: "#032b0b"
        }

        Label {
            id: label
            x: 48
            y: 358
            text: qsTr("Effect Name")
            font.pixelSize: 40
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            wrapMode: Text.NoWrap
            anchors.bottom: element1.bottom
            anchors.bottomMargin: 75
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Switch {
            id: element1
            x: 132
            y: 440
            anchors.horizontalCenterOffset: 0
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 100
            scale: 2.5
        }

        EffectDialForm {
            objectName: "dial1"
            id: effectDialForm
            anchors.top: parent.top
            anchors.topMargin: 130
            anchors.left: parent.left
            anchors.leftMargin: -10
        }

        EffectDialForm {
            objectName: "dial2"
            id: effectDialForm2
            x: 76
            y: 132
            anchors.top: parent.top
            anchors.topMargin: 130
            anchors.right: parent.right
            anchors.rightMargin: -10
        }

        EffectDialForm {
            objectName: "dial3"
            id: effectDialForm1
            x: 76
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top
            anchors.topMargin: 0
        }





    }
    states: [
        State {
            name: "State1"
        }
    ]
}

/*##^##
Designer {
    D{i:3;anchors_x:169}D{i:4;anchors_x:"-12";anchors_y:143}D{i:5;anchors_x:"-12";anchors_y:144}
D{i:6;anchors_y:"-12"}D{i:7;anchors_y:"-12"}D{i:1;anchors_height:200;anchors_width:200;anchors_x:0;anchors_y:0}
}
##^##*/
