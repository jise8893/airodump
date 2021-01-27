#ifndef AIRODUMP_H
#define AIRODUMP_H

#endif // AIRODUMP_H
#include <cstdint>
#include <string>
#include <iostream>
#include <string>
#pragma pack(push,1)
class airodump{
public:
    uint8_t beacons;
    uint8_t pwr;
    unsigned char essid[256];
};
#pragma pack(pop)
