TEMPLATE = app
CONFIG += c++11 console
CONFIG -= app_bundle
CONFIG -= qt
LIBS += -lpcap
SOURCES += \
        main.cpp

HEADERS += \
    extended_radiotap.h \
    mac.h \
    radiotap_header.h \
    dot11_frame.h \
    frame_control.h \
    airodump.h
