TEMPLATE = lib

SOURCES += \
    libsynth.cpp \
    BlepOscillator.cpp \
    ClampSound.cpp \
    Filter.cpp \
    HighFilter.cpp \
    LowFilter.cpp \
    Oscilloscope.cpp \
    ResoFilter.cpp \
    SinusGenerator.cpp \
    SoundGenerator.cpp \
    TriangleGenerator.cpp

HEADERS += libsynth.hpp

PKGCONFIG += sdl2 SDL2_mixer
CONFIG += link_pkgconfig

# does this, I think, target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES} ${SDLMIXER_LIBRARIES})

#lib.path = "/usr/share/harbour-simplesynth/lib"
#INSTALLS += lib

#TARGET +=  synth.so
#DESTDIR = "lib"
#DESTDIR = .

#DISTFILES += \
#    libsynth.pri
