#ifndef EXTENDED_RADIOTAP_H
#define EXTENDED_RADIOTAP_H

#endif // EXTENDED_RADIOTAP_H
#include <cstdint>
#include <string>
#pragma pack(push,1)
struct Extended_radiotap{
    uint8_t flags;
    uint8_t datarate;
    uint16_t channel_frequency;
    uint16_t channel_flags;
    uint8_t antenna_signal;
    uint8_t antenna;
    uint16_t rxflags;
};
#pragma pack(pop)
