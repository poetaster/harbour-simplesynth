# NOTICE:
#
# Application name defined in TARGET has a corresponding QML filename.
# If name defined in TARGET is changed, the following needs to be done
# to match new name:
#   - corresponding QML filename must be changed
#   - desktop icon filename must be changed
#   - desktop filename must be changed
#   - icon definition filename in desktop file must be changed
#   - translation filenames have to be changed

# The name of your application
TEMPLATE = app

TARGET = harbour-simplesynth

CONFIG += sailfishapp

PKGCONFIG += sdl2 SDL2_mixer sailfishapp
CONFIG += link_pkgconfig

# include our shared library and install it

LIBS += -L$$OUT_PWD/../libsynth/ -lsynthetizer

#libsynth.files += ../libsynth/libsynthetizer.so.1.0.0
#libsynth.files += ../libsynth/libsynthetizer.so.1.0
#libsynth.files += ../libsynth/libsynthetizer.so.1
#libsynth.files += ../libsynth/libsynthetizer.so
#libsynth.path = /usr/share/$${TARGET}/lib
#INSTALLS += libsynth

# additional support c++ qml  not needed
#QML_IMPORT_NAME = de.poetaster.sailsynth
#QML_IMPORT_MAJOR_VERSION = 1

QMAKE_RPATHDIR += /usr/share/$${TARGET}/lib

SOURCES += src/harbour-simplesynth.cpp \
           src/synthesizer.cpp \
           src/synthcontroller.cpp

HEADERS += 	../libsynth/include/libsynth.hpp \
                src/synthesizer.h \
                src/synthcontroller.h

INCLUDEPATH += ../libsynth/ \
                src/

OTHER_FILES += $$files(rpm/*)

DISTFILES += qml/harbour-simplesynth.qml \
    qml/cover/CoverPage.qml \
    qml/pages/FirstPage.qml \
    qml/pages/SecondPage.qml \
    qml/pages/Presets.qml \
    qml/js/*.js \
    ../rpm/harbour-simplesynth.changes.in \
    ../rpm/harbour-simplesynth.changes.run.in \
    ../rpm/harbour-simplesynth.spec \
    ../rpm/harbour-simplesynth.yaml \
    translations/*.ts \
    harbour-simplesynth.desktop

SAILFISHAPP_ICONS = 86x86 108x108 128x128 172x172

# to disable building translations every time, comment out the
# following CONFIG line
CONFIG += sailfishapp_i18n

# German translation is enabled as an example. If you aren't
# planning to localize your app, remember to comment out the
# following TRANSLATIONS line. And also do not forget to
# modify the localized app name in the the .desktop file.
# TRANSLATIONS += translations/harbour-simplesynth-de.ts
