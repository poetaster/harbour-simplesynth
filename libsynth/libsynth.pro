TEMPLATE = lib

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

QMAKE_RPATHDIR += /usr/share/$${TARGET}/lib
#INSTALLS += "/usr/share/$${TARGET}/lib"

# does this, I think, target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES} ${SDLMIXER_LIBRARIES})

# NONSENSE
TARGET = synthetizer
#DESTDIR = ../simplesynth
#INSTALLS += "/usr/share/harbour-simplesynth/lib"
#DESTDIR += "/usr/share/harbour-simplesynth/lib"
#INSTALLS += lib

#TARGET +=  synth.so
#DESTDIR = "lib"
#DESTDIR = .

#DISTFILES += \
#    libsynth.pri
