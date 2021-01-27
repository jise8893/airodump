#ifndef IP_H
#define IP_H

#endif // IP_H
#pragma once
#include <cstdint>
#include <string>
class Ip final {
    static const int Size = 4;

public:
    Ip(){}
    Ip(const uint32_t r) : ip_(r){}
    Ip(const std::string r) {}

    operator uint32_t() const { return ip_; }
    bool operator == (const Ip& r) const { return ip_ == r.ip_; }
    uint32_t ipaddr() { return ip_; }
    explicit operator std::string() const;
protected:
    uint32_t ip_;
};
