QT  += core gui svg multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Muaddin
TEMPLATE = app

SOURCES += main.cpp \
    maincore.cpp \
    settingsdisplay.cpp \
    locationtab.cpp \
    methodstab.cpp \
    maindisplay.cpp \
    mainmenubar.cpp \
    prayergroup.cpp \
    timecore.cpp \
    aboutdisplay.cpp \
    systemtraymenu.cpp \
    athan.cpp \
    athangroup.cpp \
    languagemenu.cpp

RESOURCES += \
    muaddin_res.qrc

HEADERS += \
    maincore.h \
    settingsdisplay.h \
    locationtab.h \
    methodstab.h \
    maindisplay.h \
    mainmenubar.h \
    prayergroup.h \
    timecore.h \
    aboutdisplay.h \
    systemtraymenu.h \
    athan.hpp \
    athangroup.h \
    languagemenu.h

TRANSLATIONS += \
    translations/Muaddin_ar.ts \
    translations/Muaddin_en.ts

win32:RC_ICONS += res/Icon.ico

macx:ICON += res/Icon.icns

