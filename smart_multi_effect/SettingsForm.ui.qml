import QtQuick 2.12
import QtQuick.Controls 2.5

Page {
    id: page
    width: 1024
    height: 600
    scale: 1

    title: qsTr("Settings")

    EffectEdit {
        id: effectEdit
        x: 127
        y: 0
    }
}
