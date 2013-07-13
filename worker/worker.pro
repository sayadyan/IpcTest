TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -lgsl -lgslcblas

SOURCES += main.cpp \
    integration.cpp \
    iintegrand.cpp \
    cloudintegrand.cpp \
    testintegrand.cpp \
    worker.cpp \
    iipcmessenger.cpp \
    fifoipcmessenger.cpp \
    mixedtestintegrand.cpp

HEADERS += \
    integration.h \
    iintegrand.h \
    cloudintegrand.h \
    testintegrand.h \
    worker.h \
    iipcmessenger.h \
    fifoipcmessenger.h \
    mixedtestintegrand.h

