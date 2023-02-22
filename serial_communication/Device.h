//
// Created by peter on 2/20/2023.
//

#ifndef THREEPP_VCPKG_TEST_DEVICE_H
#define THREEPP_VCPKG_TEST_DEVICE_H

#include "Serial.h"

class Device
{
private:
    const char* port;
    Serial* device;

public:
    Device();
    void setPort(const char* _port);
    bool connect();
    std::string read();
    void write(char _data[]);
    bool isConnected();
};

#endif //THREEPP_VCPKG_TEST_DEVICE_H
