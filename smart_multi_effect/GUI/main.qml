import QtQuick 2.12
import QtQuick.Controls 2.5

ApplicationWindow {
    objectName: "window"
    id: window
    visible: true
    width: 1024
    height: 600
    title: qsTr("Smart Multi Effect")

    Drawer {
        id: drawer
        width: window.width * 0.25
        height: window.height

        Column {
            anchors.fill: parent

//            ItemDelegate {
//                text: qsTr("Edit Mode")
//                width: parent.width
//                onClicked: {
//                    stackView.push("EditingForm.ui.qml")
//                    drawer.close()
//                }
//            }
//            ItemDelegate {
//                text: qsTr("Settings")
//                width: parent.width
//                onClicked: {
//                    stackView.push("SettingsForm.ui.qml")
//                    drawer.close()
//                }
//            }
        }
    }



    Button {
        id: toolButton
        text: stackView.depth > 1 ? "\u25C0" : "\u2630"

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

    Frame {
        id: frame
        objectName: "viewArea"
        anchors.bottomMargin: 100
        anchors.fill: parent
    }
}
