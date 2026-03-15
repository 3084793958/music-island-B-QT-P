QT += core gui widgets x11extras multimedia multimediawidgets dbus
LIBS += -lX11  -lXtst
TEMPLATE = lib
CONFIG += plugin
TARGET = Music-Island

HEADERS += \
    informationwidget.h \
    showkeyplugin.h \
    keyscan.h \
    informationpopup.h \
    informationlyric.h \
    informationgetmusic.h \
    interfaces/constants.h \
    interfaces/pluginproxyinterface.h \
    interfaces/pluginsiteminterface.h

SOURCES += \
    showkeyplugin.cpp \
    informationwidget.cpp \
    keyscan.cpp \
    informationpopup.cpp \
    informationlyric.cpp \
    informationgetmusic.cpp \
    interfaces/pluginsiteminterface.cpp

DISTFILES += \
    music-island.json

RESOURCES += \
    music-island.qrc
