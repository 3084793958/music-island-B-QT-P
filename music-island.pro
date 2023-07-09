QT += core gui widgets x11extras multimedia multimediawidgets
LIBS += -lX11  -lXtst
TEMPLATE = lib
CONFIG += plugin
TARGET = Music-Island

HEADERS += \
    informationwidget.h \
    showkeyplugin.h \
    keyscan.h \
    informationpopup.h \
    informationlyric.h

SOURCES += \
    showkeyplugin.cpp \
    informationwidget.cpp \
    keyscan.cpp \
    informationpopup.cpp \
    informationlyric.cpp

DISTFILES += \
    music-island.json

RESOURCES += \
    music-island.qrc
