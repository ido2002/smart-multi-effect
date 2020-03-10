import QtQuick 2.12
import QtQuick.Controls 2.5
import "ButtonsArea"

ApplicationWindow {
    objectName: "window"
    id: window
    visibility: "FullScreen"
    visible: true
    width: 1024
    height: 600
    title: qsTr("Smart Multi Effect")

    Frame {
        id: frame
        objectName: "viewArea"
        anchors.bottomMargin: 100
        anchors.fill: parent
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
        width: window.width * 0.25
        height: window.height

        Column {
            anchors.fill: parent

            ItemDelegate {
                id: fullScreenButton
                text: qsTr("Exit Full Screen")
                width: parent.width
                onClicked: {
                    if(fullScreenButton.text === "Full Screen") {
                        window.visibility = "FullScreen";
                        fullScreenButton.text = "Exit Full Screen";
                    } else {
                        window.visibility = "Windowed";
                        fullScreenButton.text = "Full Screen";
                    }
                }
            }

            ItemDelegate {
                text: qsTr("exit")
                width: parent.width
                onClicked: {
                    window.close();
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
            drawer.open()
        }
    }

}

/*##^##
Designer {
    D{i:5;anchors_x:195}
}
##^##*/
