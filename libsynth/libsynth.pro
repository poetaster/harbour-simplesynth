TEMPLATE = lib
CONFIG += qt warn_on
QT -= gui

SOURCES += \
    src/libsynth.cpp \
    src/BlepOscillator.cpp \
    src/ClampSound.cpp \
    src/Filter.cpp \
    src/HighFilter.cpp \
    src/LowFilter.cpp \
    src/Oscilloscope.cpp \
    src/ResoFilter.cpp \
    src/SinusGenerator.cpp \
    src/SoundGenerator.cpp \
    src/TriangleGenerator.cpp

HEADERS += include/libsynth.hpp

PKGCONFIG += sdl2 SDL2_mixer
CONFIG += link_pkgconfig

# does this, I think, target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES} ${SDLMIXER_LIBRARIES})

# NONSENSE
TARGET = lsynthetizer

#DEFINES += QUAZIP_BUILD
#CONFIG(staticlib): DEFINES += QUAZIP_STATIC

CONFIG += staticlib

target.path=/usr/share/harbour-simplesynth/lib

INSTALLS += target
