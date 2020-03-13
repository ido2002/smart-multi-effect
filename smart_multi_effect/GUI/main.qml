import QtQuick 2.12
import QtQuick.Controls 2.5
import "ButtonsArea"
import "EffectEdit"

ApplicationWindow {
    objectName: "window"
    id: window
    visibility: "FullScreen"
    visible: true
    width: 1024
    height: 600
    title: qsTr("Smart Multi Effect")

    function openDrawer_f() {
        drawer.open();
    }
    function closeDrawer_f() {
        drawer.close();
    }

    function exit_f() {
        window.close();
    }

    function fullScreen_f() {
        if(fullScreenButton.text === "Full Screen") {
            window.visibility = "FullScreen";
            fullScreenButton.text = "Exit Full Screen";
        } else {
            window.visibility = "Windowed";
            fullScreenButton.text = "Full Screen";
        }
    }



    Frame {
        id: frame
        objectName: "viewArea"
        anchors.bottomMargin: 100
        anchors.fill: parent
    }

    PresetEditPage {
        id: presetEditPage
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.top: parent.top
        anchors.topMargin: 0
    }

    ButtonArea {
        objectName: "buttonsArea"
        id: buttonArea
        y: 500
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0
    }

    Drawer {
        id: drawer
        objectName: "drawer"
        width: window.width * 0.25
        height: window.height


        Column {
            anchors.fill: parent

            ItemDelegate {
                id: fullScreenButton
                text: qsTr("Exit Full Screen")
                width: parent.width
                onClicked: {
                    window.fullScreen_f();
                }
            }

            ItemDelegate {
                text: qsTr("exit")
                width: parent.width
                onClicked: {
                    window.exit_f();
                }
            }
        }
    }

    Button {
        id: toolButton
        text: "\u2630"

        width: 50
        height: 56

        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.top: parent.top
        anchors.topMargin: 0


        font.pixelSize: Qt.application.font.pixelSize * 1.6

        onClicked: {
            window.openDrawer_f();
        }
    }
}


