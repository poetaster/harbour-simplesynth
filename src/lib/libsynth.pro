TEMPLATE = lib
#QT += qml multimedia network websockets

#include(defines.pri)
#include(../harbour-sailfin.pri)

SOURCES += \
    lib/libsynth.cpp \

HEADERS += \
    include/libsynth.hpp \

#VERSION = $$SAILFIN_VERSION

TARGET =
DESTDIR = lib
