#-------------------------------------------------
#  Copyright 2019 ESRI
#
#  All rights reserved under the copyright laws of the United States
#  and applicable international laws, treaties, and conventions.
#
#  You may freely redistribute and use this sample code, with or
#  without modification, provided you include the original copyright
#  notice and use restrictions.
#
#  See the Sample code usage restrictions document for further information.
#-------------------------------------------------

TARGET = Simulator 
TEMPLATE = app

CONFIG += c++14

# additional modules are pulled in via arcgisruntime.pri
QT += opengl widgets core


equals(QT_MAJOR_VERSION, 5) {
    lessThan(QT_MINOR_VERSION, 12) { 
        error("$$TARGET requires Qt 5.12.6")
    }
	equals(QT_MINOR_VERSION, 12) : lessThan(QT_PATCH_VERSION, 6) {
		error("$$TARGET requires Qt 5.12.6")
	}
}

ARCGIS_RUNTIME_VERSION = 100.8
include($$PWD/arcgisruntime.pri)

win32:CONFIG += \
    embed_manifest_exe

SOURCES += \
    collector.cpp \
    framedata.cpp \
    header.cpp \
    main.cpp \
    Simulator.cpp  \
    mapobject.cpp \
    pedestrian.cpp \
    pole.cpp \
    polearray.cpp \
    vehicle.cpp

HEADERS += \
    Simulator.h \
    collector.h \
    framedata.h \
    header.h \
    mapobject.h \
    pedestrian.h \
    pole.h \
    polearray.h \
    vehicle.h

#-------------------------------------------------------------------------------
