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

};
#pragma pack(pop)
