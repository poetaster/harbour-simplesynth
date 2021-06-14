TEMPLATE = subdirs

SUBDIRS += \
    libsynth \
    simplesynth

simplesynth.depends = libsynth

OTHER_FILES += 	rpm/harbour-simplesynth.yaml \
                rpm/harbour-simplesynth.spec
