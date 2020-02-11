import QtQuick 2.12
import QtQuick.Controls 2.5

Item {
    id: element
    width: 150
    height: 150

    Dial {
        objectName: "dial"
        id: dial
        x: 0
        anchors.top: parent.top
        anchors.topMargin: 0
        anchors.horizontalCenter: parent.horizontalCenter
        value:  0.5
    }

    Label {
        id: labelname
        objectName: "textLable"
        x: 64
        y: 134
        width: 144
        height: 42
        text: qsTr("Label")
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        anchors.horizontalCenter: parent.horizontalCenter
        font.pixelSize: 30
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
    }

    Label {
        id: labelval
        objectName: "valueLable"
        x: -6
        y: 43
        text: (dial.position * 100).toFixed(0)
        font.bold: false
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        font.pixelSize: 35
        anchors.verticalCenterOffset: 0
        anchors.horizontalCenterOffset: 0
        anchors.horizontalCenter: dial.horizontalCenter
        anchors.verticalCenter: dial.verticalCenter
    }
}

/*##^##
Designer {
    D{i:1;anchors_y:0}D{i:2;anchors_x:64}
}
##^##*/
