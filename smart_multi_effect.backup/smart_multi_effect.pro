QT += quick

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
        EffectController/potentiometer.cpp \
        EffectController/relay.cpp \
        RiffRecognition/riff.cpp \
        SoundProcessing/neuralnetwork.cpp \
        SoundProcessing/soundcard.cpp \
        SoundProcessing/soundprocessor.cpp \
        SoundProcessing/stroke.cpp \
        main.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
#qnx: target.path = /tmp/$${TARGET}/bin
#else: unix:!android: target.path = /opt/$${TARGET}/bin
#!isEmpty(target.path): INSTALLS += target

target.path = smart_multi_effect_App
INSTALLS += target

HEADERS += \
    EffectController/effect.h \
    EffectController/effectcontroller.h \
    EffectController/gpiocontrol.h \
    EffectController/potentiometer.h \
    EffectController/relay.h \
    RiffRecognition/riff.h \
    SoundProcessing/neuralnetwork.h \
    SoundProcessing/soundcard.h \
    SoundProcessing/soundprocessor.h \
    SoundProcessing/stroke.h