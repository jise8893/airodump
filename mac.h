#ifndef MAC_H
#define MAC_H

#endif // MAC_H
#pragma once
#include <cstdint>
#include <cstring>
#include <string>
#include <iostream>
class Mac final {
        static const int SIZE = 6;

public :

        Mac() {};
        Mac(const uint8_t* r) { memcpy(this->mac_, r, SIZE); };
        Mac(const std::string r);

        operator uint8_t* () const { return const_cast<uint8_t*>(mac_); }
        bool operator == (const Mac& r) const { return memcmp(mac_, r.mac_, SIZE); }
protected:
        uint8_t mac_[SIZE] = { 0, };
};
