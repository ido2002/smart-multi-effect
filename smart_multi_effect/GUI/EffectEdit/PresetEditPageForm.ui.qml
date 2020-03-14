import QtQuick 2.4
import QtQuick.Controls 2.3

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
        anchors.fill: parent
        source: "PresetBackground.png"
        fillMode: Image.PreserveAspectCrop

        //            Slider {
        //                id: slider
        //                snapMode: Slider.SnapAlways
        //                stepSize: 1
        //                to: 100
        //                from: 1
        //                objectName: "resSlider"
        //                anchors.left: parent.left
        //                anchors.leftMargin: 297
        //                anchors.top: parent.top
        //                anchors.topMargin: 96
        //                value: 1

        //                Label {
        //                    id: label
        //                    y: 22
        //                    text: slider.value
        //                    font.pointSize: 18
        //                    verticalAlignment: Text.AlignVCenter
        //                    anchors.verticalCenter: parent.verticalCenter
        //                    anchors.left: parent.right
        //                    anchors.leftMargin: 0
        //                }

        //                Label {
        //                    id: labelT
        //                    y: 19
        //                    text: qsTr("jump size:")
        //                    anchors.right: parent.left
        //                    anchors.rightMargin: 0
        //                    font.pointSize: 18
        //                    verticalAlignment: Text.AlignVCenter
        //                    anchors.verticalCenter: parent.verticalCenter
        //                }
        //            }

        //            Slider {
        //                id: slider1
        //                snapMode: Slider.SnapAlways
        //                stepSize: 0.1
        //                to: 5
        //                objectName: "timeSlider"
        //                anchors.left: parent.left
        //                anchors.leftMargin: 297
        //                anchors.top: parent.top
        //                anchors.topMargin: 143
        //                value: 0

        //                Label {
        //                    id: label1
        //                    y: 19
        //                    text: slider1.value.toFixed(1)
        //                    font.pointSize: 18
        //                    verticalAlignment: Text.AlignVCenter
        //                    anchors.verticalCenter: parent.verticalCenter
        //                    anchors.left: parent.right
        //                    anchors.leftMargin: 0
        //                }

        //                Label {
        //                    id: label1T
        //                    x: -106
        //                    y: 19
        //                    width: 106
        //                    height: 29
        //                    text: qsTr("time[sec]:")
        //                    anchors.right: parent.left
        //                    anchors.rightMargin: 0
        //                    font.pointSize: 18
        //                    verticalAlignment: Text.AlignVCenter
        //                    anchors.verticalCenter: parent.verticalCenter
        //                }
        //            }
    }

    Text {
        id: headLine
        objectName: "presetHeadline"
        x: 0
        y: 42
        width: 1024
        height: 80
        color: "#efeeee"
        text: qsTr("preset name")
        font.bold: true
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        font.pixelSize: 59
    }


    Item {
        id: element6
        objectName: "effect_6"
        x: 709
        y: 303
        width: 280
        height: 160
        anchors.right: element3.right
        anchors.rightMargin: 0
        anchors.bottom: element4.bottom
        anchors.bottomMargin: 0
    }

    Item {
        id: element5
        objectName: "effect_5"
        x: 365
        y: 303
        width: 280
        height: 160
        anchors.horizontalCenterOffset: 0
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: element4.bottom
        anchors.bottomMargin: 0
    }

    Item {
        id: element4
        objectName: "effect_4"
        x: 29
        y: 303
        width: 280
        height: 160
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 30
        anchors.leftMargin: 0
        anchors.left: element1.left
    }

    Item {
        id: element3
        objectName: "effect_3"
        x: 680
        y: 170
        width: 280
        height: 160
        anchors.bottom: element1.bottom
        anchors.rightMargin: 35
        anchors.right: parent.right
        anchors.bottomMargin: 0
    }

    Item {
        id: element2
        objectName: "effect_2"
        x: 365
        y: 137
        width: 280
        height: 160
        anchors.horizontalCenterOffset: 0
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: element1.bottom
        anchors.bottomMargin: 0
    }

    Item {
        id: element1
        x: 29
        y: 131
        objectName: "effect_1"
        width: 280
        height: 160
        anchors.top: parent.top
        anchors.topMargin: 130
        anchors.left: parent.left
        anchors.leftMargin: 35
    }










}

/*##^##
Designer {
    D{i:2;anchors_x:-171;anchors_y:-54}D{i:3;anchors_x:200;anchors_y:185}D{i:4;anchors_height:160;anchors_x:200;anchors_y:185}
D{i:5;anchors_height:160;anchors_x:200;anchors_y:185}D{i:6;anchors_height:160;anchors_x:200;anchors_y:185}
D{i:7;anchors_height:160;anchors_x:200;anchors_y:185}D{i:8;anchors_height:160;anchors_x:200;anchors_y:185}
D{i:9;anchors_x:297;anchors_y:96}
}
##^##*/

