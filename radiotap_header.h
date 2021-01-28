#pragma once
#include <cstdint>
#include <cstring>
#pragma pack(push,1)
class Ieee80211_radiotap_header{

public:
    uint8_t it_version;
    uint8_t it_pad;
    uint16_t it_len;
    uint32_t it_present;
    uint8_t flags;
    uint8_t datarate;
    uint16_t channel_frequency;
    uint16_t channel_flags;
    uint8_t antenna_signal;
    uint8_t antenna;
    uint16_t rxflags;
};
#pragma pack(pop)
