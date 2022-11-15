QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \

HEADERS += \
    Core.h \
    Core_Version.h \
    Hardware.h \
    Librairie.h \
    MfErrNo.h \
    Sw_Device.h \
    Sw_ISO14443-4.h \
    Sw_ISO14443A-3.h \
    Sw_Mf_Classic.h \
    Sw_Poll.h \
    Tools.h \
    TypeDefs.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    ODALID_Education.dll \
    img/nfc.png \
    libODALID_Education.a

RESOURCES += \
    ressources.qrc
