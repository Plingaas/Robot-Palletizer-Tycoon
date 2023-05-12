//
// Created by peter on 2/20/2023.
//

#ifndef THREEPP_VCPKG_TEST_DEVICE_H
#define THREEPP_VCPKG_TEST_DEVICE_H

#include <array>
#include "Serial.hpp"

/**
 * @brief A class for a COM device.
 */
class Device {

private:
    const char *port;
    std::unique_ptr<Serial> device;

public:

    /**
     * @brief The Device's constructor.
     */
    Device();

    /**
     * @brief Sets the COM port.
     *
     * @param _port The COM port to connect to.
     */
    void setPort(const char *_port);

    /**
     * @brief Gets the port..
     *
     * @return Returns the port as a const char*
     */
    const char* getPort();
    /**
     * @brief Connects to the stored port.
     *
     * @return Returns a bool for whether the connection was successful or not.
     */
    bool connect();

    /**
     * @brief Reads from the serial port.
     *
     * @return Returns a std::string containing the serial data.
     */
    std::string read();

    /**
     * @brief Writes to the serial port.
     *
     * @param _data The data to write.
     *
     * @return void.
     */
    void write(char _data[]);

    /**
     * @brief Checks if the Device is connected.
     *
     * @return Returns a boolean for whether the device is connected or not.
     */
    bool isConnected();

};

#endif //THREEPP_VCPKG_TEST_DEVICE_H
