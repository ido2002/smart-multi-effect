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
        width: 100
        height: 100
        scale: 1
        font.pointSize: 20
        anchors.top: parent.top
        anchors.topMargin: 0
        anchors.horizontalCenter: parent.horizontalCenter
        value:  0.2
    }

    Label {
        id: labelname
        objectName: "textLabel"
        x: 64
        y: 106
        width: 144
        height: 42
        text: qsTr("Label")
        font.family: "Verdana"
        anchors.horizontalCenterOffset: 0
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        anchors.horizontalCenter: parent.horizontalCenter
        font.pixelSize: 30
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 2
    }

    Label {
        id: labelval
        objectName: "valueLabel"
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
