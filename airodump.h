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
    uint8_t essid[256]={0,};
    uint8_t len=0;
};
#pragma pack(pop)
