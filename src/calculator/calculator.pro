QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../parser.c \
    ../smartcalc.c \
    ../stack.c \
    main.cpp \
    qcustomplot.cpp \
    smartcalc_v1.cpp

HEADERS += \
    ../smartcalc.h \
    qcustomplot.h \
    smartcalc_v1.h

FORMS += \
    smartcalc_v1.ui

TRANSLATIONS += \
    calculator_en_001.ts
CONFIG += release
CONFIG += embed_translations

win32: RC_ICONS += images/icon.ico
unix: RC_ICONS += images/icon.png
macx: ICON = images/256.icns

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    images/icon.ico \
    images/256.icns \
	images/icon.png \
    images/text5574.png

RESOURCES += \
    sources.qrc
