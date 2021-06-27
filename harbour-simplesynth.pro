TEMPLATE = subdirs
TARGET = harbour-simplesynth

SUBDIRS += \
    libsynth \
    simplesynth


#simplesynth.depends = libsynthetizer

OTHER_FILES += 	rpm/harbour-simplesynth.yaml \
                rpm/harbour-simplesynth.spec
#message($$SUBDIRS)
