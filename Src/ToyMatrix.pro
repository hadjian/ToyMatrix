#-------------------------------------------------
#
# Project created by QtCreator 2013-02-24T01:08:36
#
#-------------------------------------------------

QT       -= core gui

TARGET = ToyMatrix
TEMPLATE = lib

DEFINES += TOYMATRIX_LIBRARY

SOURCES +=

HEADERS += toymatrix.h \
    toyvector.h

symbian {
    MMP_RULES += EXPORTUNFROZEN
    TARGET.UID3 = 0xE1F14559
    TARGET.CAPABILITY = 
    TARGET.EPOCALLOWDLLDATA = 1
    addFiles.sources = ToyMatrix.dll
    addFiles.path = !:/sys/bin
    DEPLOYMENT += addFiles
}

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}

unix:!symbian: LIBS += -L$$PWD/../../gtest-1.6.0/src/ -lgtest

INCLUDEPATH += $$PWD/../../gtest-1.6.0/include
DEPENDPATH += $$PWD/../../gtest-1.6.0/include

unix:!symbian: PRE_TARGETDEPS += $$PWD/../../gtest-1.6.0/src/libgtest.a
