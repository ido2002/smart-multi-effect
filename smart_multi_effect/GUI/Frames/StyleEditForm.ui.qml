import QtQuick 2.4
import QtQuick.Controls 2.5

Item {
    id: element
    width: 990
    height: 100

    Rectangle {
        id: rectangle
        objectName: "rectangle"
        x: 592
        y: 74
        width: 950
        color: "#f48e06"
        anchors.rightMargin: 0
        anchors.bottomMargin: 0
        anchors.leftMargin: 0
        anchors.topMargin: 0
        opacity: 0.5
        anchors.fill: parent
    }

    ComboBox {
        id: comboBoxSet
        anchors.right: sliderBassFactor.left
        anchors.rightMargin: 0
        font.pointSize: 24
        displayText: currentText
        textRole: ""
        objectName: "comboBoxSet"
        anchors.left: label2.right
        anchors.leftMargin: 3
        anchors.top: parent.top
        anchors.topMargin: 0

        model: []
    }

    ComboBox {
        id: comboBoxPreset
        objectName: "comboBoxPreset"
        y: 52
        displayText: currentText
        font.pointSize: 20
        anchors.left: label3.right
        anchors.leftMargin: 3
        anchors.right: comboBoxSet.right
        anchors.rightMargin: 0
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0

        model: []
    }

    Label {
        id: label
        x: 525
        y: 74
        text: qsTr("Base")
        anchors.horizontalCenter: dialBase.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        font.pointSize: 16
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
    }

    Dial {
        id: dialBase
        objectName: "dialBase"
        x: 464
        y: -5
        anchors.right: sliderHighFactor.left
        anchors.rightMargin: -15
        stepSize: 0.05
        anchors.verticalCenter: parent.verticalCenter
        anchors.verticalCenterOffset: -10
        scale: 0.7
    }

    Dial {
        id: dialHigh
        objectName: "dialHigh"
        x: 490
        y: -5
        stepSize: 0.05
        anchors.right: labelHighFreq.right
        anchors.rightMargin: 73
        anchors.verticalCenterOffset: -10
        anchors.verticalCenter: parent.verticalCenter
        scale: 0.7
    }

    Slider {
        id: sliderThreashold
        objectName: "sliderThreashold"
        y: 61
        width: 230
        height: 39
        to: 1
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        value: 0.7
    }

    ProgressBar {
        id: progressBar
        objectName: "progressBar"
        x: 107
        y: 26
        width: 22
        height: 5
        to: 1
        anchors.horizontalCenterOffset: 1
        anchors.verticalCenterOffset: -43
        anchors.horizontalCenter: sliderThreashold.horizontalCenter
        anchors.verticalCenter: sliderThreashold.verticalCenter
        scale: 10
        value: 0.2
    }

    Slider {
        id: sliderBass
        objectName: "sliderBass"
        y: 70
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        stepSize: 5
        to: 500
        from: 60
        anchors.right: sliderHigh.right
        anchors.rightMargin: 0
        anchors.left: sliderHigh.left
        anchors.leftMargin: 0
        value: 200
    }

    Slider {
        id: sliderHigh
        objectName: "sliderHigh"
        x: 592
        width: 190
        anchors.top: parent.top
        anchors.topMargin: 0
        anchors.right: parent.right
        anchors.rightMargin: 6
        stepSize: 5
        to: 350
        from: 1500
        rotation: 180
        orientation: Qt.Horizontal
        wheelEnabled: false
        value: 500
    }

    Label {
        id: labelBaseFreq
        x: 522
        y: 82
        text: sliderBass.value + "Hz"
        anchors.verticalCenter: sliderBass.verticalCenter
        anchors.right: sliderBass.left
        anchors.rightMargin: 6
        font.pointSize: 20
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignLeft
    }

    Label {
        id: labelHighFreq
        x: 522
        y: 25
        text: sliderHigh.value + "Hz"
        anchors.right: sliderHigh.left
        anchors.rightMargin: 6
        anchors.verticalCenter: sliderHigh.verticalCenter
        font.pointSize: 20
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignLeft
    }

    Label {
        id: labelHigh
        x: 512
        y: 16
        text: dialHigh.value.toFixed(2)
        anchors.horizontalCenter: dialHigh.horizontalCenter
        anchors.verticalCenterOffset: 0
        font.pointSize: 20
        horizontalAlignment: Text.AlignHCenter
        anchors.verticalCenter: dialHigh.verticalCenter
        verticalAlignment: Text.AlignVCenter
    }

    Label {
        id: labelBase
        x: 392
        y: 73
        text: dialBase.value.toFixed(2)
        anchors.horizontalCenter: dialBase.horizontalCenter
        anchors.verticalCenterOffset: 0
        font.pointSize: 20
        horizontalAlignment: Text.AlignHCenter
        anchors.verticalCenter: dialBase.verticalCenter
        verticalAlignment: Text.AlignVCenter
    }

    Label {
        id: label1
        x: 627
        y: 74
        text: qsTr("High")
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        anchors.horizontalCenter: dialHigh.horizontalCenter
        font.pointSize: 16
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
    }

    Label {
        id: label2
        y: 8
        text: qsTr("Set:")
        anchors.left: label3.left
        anchors.leftMargin: 0
        anchors.verticalCenter: comboBoxSet.verticalCenter
        font.pointSize: 20
        verticalAlignment: Text.AlignVCenter
    }

    Label {
        id: label3
        y: 59
        text: qsTr("Preset:")
        anchors.left: sliderThreashold.right
        anchors.leftMargin: 5
        anchors.verticalCenter: comboBoxPreset.verticalCenter
        font.pointSize: 20
        verticalAlignment: Text.AlignVCenter
    }

    Slider {
        id: sliderBassFactor
        objectName: "sliderBassFactor"
        x: 424
        width: 25
        stepSize: 1
        to: 50
        anchors.right: dialBase.left
        anchors.rightMargin: -15
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        anchors.top: parent.top
        anchors.topMargin: 0
        orientation: Qt.Vertical
        value: 25
    }

    Slider {
        id: sliderHighFactor
        objectName: "sliderHighFactor"
        x: 583
        width: 34
        stepSize: 1
        to: 50
        anchors.right: dialHigh.left
        anchors.rightMargin: -15
        anchors.top: parent.top
        anchors.topMargin: 0
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        value: 25
        orientation: Qt.Vertical
    }
}

/*##^##
Designer {
    D{i:1;anchors_height:200;anchors_width:200}D{i:2;anchors_x:387;anchors_y:0}D{i:3;anchors_x:387}
D{i:4;anchors_x:265;anchors_y:70}D{i:5;anchors_x:265;anchors_y:17}D{i:6;anchors_y:17}
D{i:16;anchors_x:308}D{i:17;anchors_x:308}D{i:18;anchors_height:100;anchors_y:0}D{i:19;anchors_height:100;anchors_y:0}
}
##^##*/

