#ifndef DOT11_BEACON_H
#define DOT11_BEACON_H

#endif // DOT11_BEACON_H
#include "ip.h"
#include "mac.h"
#include "radiotap_header.h"
#include "frame_control.h"
#pragma pack(push,1)
class Dot11_frame {
public:

    Frame_control frame_control;//check frame to ds or from ds
    uint16_t duration_id;
    Mac address_1; //receiver address or destination
    Mac address_2; //transmitter or source address
    Mac address_3; // bssid address
    uint16_t sequence_control;

    unsigned char timestamp[8];
    uint16_t beacon_intervals;
    uint32_t capability_information;

    uint8_t ssid_param:4;
    uint8_t tag_length:4;

};
#pragma pack(pop)
