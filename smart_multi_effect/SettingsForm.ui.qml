import QtQuick 2.12
import QtQuick.Controls 2.5

Page {
    id: page
    width: 1024
    height: 600
    scale: 1

    title: qsTr("Settings")

    Text {
        id: element
        x: 169
        y: 147
        width: 371
        height: 144
        text: qsTr("Text")
        font.pixelSize: 12
    }

    EffectDial {
        id: effectDial
        x: 396
        y: 132
    }

    EffectEdit {
        id: effectEdit
        x: 620
        y: 0
    }

    EffectEdit {
        id: effectEdit1
        x: -13
        y: 77
        scale: 0.5
    }
}
