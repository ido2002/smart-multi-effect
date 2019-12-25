QT += quick

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
    EffectController/gpioread.h \
    EffectController/potentiometer.h \
    EffectController/preset.h \
    RiffRecognition/riff.h \
    SoundProcessing/neuralnetwork.h \
    SoundProcessing/soundcard.h \
    SoundProcessing/soundprocessor.h \
    SoundProcessing/stroke.h \
    conf.h

DISTFILES += \
    EffectController/WiringPi-master/COPYING.LESSER \
    EffectController/WiringPi-master/INSTALL \
    EffectController/WiringPi-master/People \
    EffectController/WiringPi-master/README.TXT \
    EffectController/WiringPi-master/VERSION \
    EffectController/WiringPi-master/build \
    EffectController/WiringPi-master/debian-template/wiringPi/DEBIAN/control \
    EffectController/WiringPi-master/debian-template/wiringPi/DEBIAN/postinst \
    EffectController/WiringPi-master/debian-template/wiringPi/DEBIAN/postrm \
    EffectController/WiringPi-master/debian/changelog \
    EffectController/WiringPi-master/debian/compat \
    EffectController/WiringPi-master/debian/control \
    EffectController/WiringPi-master/debian/copyright \
    EffectController/WiringPi-master/debian/libwiringpi-dev.dirs \
    EffectController/WiringPi-master/debian/libwiringpi-dev.install \
    EffectController/WiringPi-master/debian/libwiringpi2.install \
    EffectController/WiringPi-master/debian/libwiringpi2.shlibs \
    EffectController/WiringPi-master/debian/rules \
    EffectController/WiringPi-master/debian/wiringpi.dirs \
    EffectController/WiringPi-master/debian/wiringpi.install \
    EffectController/WiringPi-master/examples/COPYING.LESSER \
    EffectController/WiringPi-master/examples/README.TXT \
    EffectController/WiringPi-master/examples/blink.rtb \
    EffectController/WiringPi-master/examples/blink.sh \
    EffectController/WiringPi-master/examples/q2w/blink.sh \
    EffectController/WiringPi-master/gpio/COPYING.LESSER \
    EffectController/WiringPi-master/gpio/gpio.1 \
    EffectController/WiringPi-master/gpio/pintest \
    EffectController/WiringPi-master/gpio/test.sh \
    EffectController/WiringPi-master/newVersion \
    EffectController/WiringPi-master/pins/pins.pdf \
    EffectController/WiringPi-master/pins/pins.tex \
    EffectController/WiringPi-master/update \
    EffectController/WiringPi-master/wiringPi/COPYING.LESSER \
    EffectController/WiringPi-master/wiringPi/noMoreStatic
