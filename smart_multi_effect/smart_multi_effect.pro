QT += quick quickwidgets charts

QT += multimedia

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Refer to the documentation for the
# deprecated API to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        EffectController/effect.cpp \
        EffectController/effectcontroller.cpp \
        EffectController/gpiocontrol.cpp \
        EffectController/gpioread.cpp \
        EffectController/potentiometer.cpp \
        EffectController/preset.cpp \
        GUI/Elements/autoswitchsetswindow.cpp \
        GUI/Elements/autoswitchsetwindowedit.cpp \
        GUI/Elements/effect_gui.cpp \
        GUI/Elements/guibutton.cpp \
        GUI/Elements/guimanager.cpp \
        GUI/Elements/loadingpage.cpp \
        GUI/Elements/managedata.cpp \
        GUI/Elements/menu.cpp \
        GUI/Elements/presetswindow.cpp \
        GUI/Elements/presetwindow.cpp \
        GUI/Elements/recordnote.cpp \
        GUI/Elements/recordoctave.cpp \
        GUI/Elements/testgui.cpp \
        GUI/Elements/train.cpp \
        RiffRecognition/riff.cpp \
        RiffRecognition/riffrecognition.cpp \
        SoundProcessing/neuralnetwork.cpp \
        SoundProcessing/noterecognition.cpp \
        SoundProcessing/soundcard.cpp \
        SoundProcessing/soundprocessor.cpp \
        SoundProcessing/stroke.cpp \
        jsonreader.cpp \
        main.cpp \
        mytimer.cpp \
        smartmultieffect.cpp \
        tobinary.cpp

RESOURCES += GUI/qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
#qnx: target.path = /tmp/$${TARGET}/bin
#else: unix:!android: target.path = /opt/$${TARGET}/bin
#!isEmpty(target.path): INSTALLS += target

target.path = .smart_multi_effect
INSTALLS += target

HEADERS += \
    EffectController/effect.h \
    EffectController/effectcontroller.h \
    EffectController/gpiocontrol.h \
    EffectController/gpioread.h \
    EffectController/potentiometer.h \
    EffectController/preset.h \
    GUI/Elements/autoswitchsetswindow.h \
    GUI/Elements/autoswitchsetwindowedit.h \
    GUI/Elements/effect_gui.h \
    GUI/Elements/guibutton.h \
    GUI/Elements/guimanager.h \
    GUI/Elements/loadingpage.h \
    GUI/Elements/managedata.h \
    GUI/Elements/menu.h \
    GUI/Elements/presetswindow.h \
    GUI/Elements/presetwindow.h \
    GUI/Elements/recordnote.h \
    GUI/Elements/recordoctave.h \
    GUI/Elements/testgui.h \
    GUI/Elements/train.h \
    RiffRecognition/riff.h \
    RiffRecognition/riffrecognition.h \
    SoundProcessing/FFT.h \
    SoundProcessing/neuralnetwork.h \
    SoundProcessing/noterecognition.h \
    SoundProcessing/soundcard.h \
    SoundProcessing/soundprocessor.h \
    SoundProcessing/stroke.h \
    conf.h \
    jsonreader.h \
    mytimer.h \
    smartmultieffect.h \
    tobinary.h
