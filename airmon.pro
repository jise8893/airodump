TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt
LIBS += -lpcap
SOURCES += \
        main.cpp

HEADERS += \
    mac.h \
    radiotap_header.h \
    dot11_frame.h \
    frame_control.h \
    airodump.h
