import QtQuick 2.12

Item {
    id: element
    width: 1024
    height: 100
    
    Rectangle {
        id: rectangle
        x: 0
        y: 16
        width: 1024
        height: 100
        color: "#343434"
        anchors.verticalCenterOffset: 0
        anchors.verticalCenter: parent.verticalCenter

        Row {
            id: row
            anchors.rightMargin: 12
            anchors.leftMargin: 12
            anchors.topMargin: 10
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 10
            anchors.top: parent.top
            anchors.right: parent.right
            anchors.left: parent.left
            spacing: 10

            CustomBuotton {
                objectName: "button_1"
                id: customBuotton
            }

            CustomBuotton {
                objectName: "button_2"
                id: customBuotton1
            }

            CustomBuotton {
                objectName: "button_3"
                id: customBuotton4
            }

            CustomBuotton {
                objectName: "button_4"
                id: customBuotton3
            }

            CustomBuotton {
                objectName: "button_5"
                id: customBuotton2
            }
        }
    }
}
