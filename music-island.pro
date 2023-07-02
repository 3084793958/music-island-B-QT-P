QT += core gui widgets x11extras multimedia multimediawidgets
LIBS += -lX11  -lXtst
TEMPLATE = lib
CONFIG += plugin
TARGET = Music-Island

HEADERS += \
    informationwidget.h \
    showkeyplugin.h \
    keyscan.h \
    informationpopup.h

SOURCES += \
    showkeyplugin.cpp \
    informationwidget.cpp \
    keyscan.cpp \
    informationpopup.cpp

DISTFILES += \
    music-island.json

RESOURCES += \
    music-island.qrc
