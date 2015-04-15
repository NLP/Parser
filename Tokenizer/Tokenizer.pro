# Author:
#       Copyright © 2015 Tony Lim <atomictheorist@gmail.com>
#       Distributed under terms of the MIT license.

TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS += -std=c++11

SOURCES += main.cpp \
    stokenize.cpp \
    token.cpp \

HEADERS += \
    stokenize.h \
    token.h \
