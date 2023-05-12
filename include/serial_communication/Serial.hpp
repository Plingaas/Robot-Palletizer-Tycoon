//
// Code from https://github.com/manashmandal/SerialPort
//
// Contains all Serial communication functionality.
// Read() Write() Connect() etc..
//
// availablePorts() written by Peter
//
#pragma once
#ifdef WIN32
#define ARDUINO_WAIT_TIME 2000
#define MAX_DATA_LENGTH 255

#include <Windows.h>
#include <iostream>
#include <vector>
#include <cstdio>
#include <string>

class Serial {
private:
    HANDLE handler;
    bool connected;
    COMSTAT status;
    DWORD errors;

public:

    /**
     * @brief The Serial's constructor.
     *
     * @param portName The port to connect to.
     */
    explicit Serial(const char *portName);

    /**
     * @brief Reads serial data.
     *
     * Reads bytes from serial port to buffer
     *
     * @param buffer The buffer to read to.
     * @param buf_size The buffer size.
     *
     * @return Returns read bytes count, or if an error occurs it returns 0.
     */
    int readSerialPort(const char *buffer, unsigned int buf_size);

    /**
     * @brief Writes serial data.
     *
     * @param buffer The buffer to send to the serial port.
     * @param buf_size The buffer size.
     *
     * @return Returns true if write succeeded and false if not.
     */
    bool writeSerialPort(const char *buffer, unsigned int buf_size);

    /**
     * @brief Checks if it's connected to a device.
     *
     * @return Returns a boolean stating whether it's connected or not.
     */
    bool isConnected();

    /**
     * @brief Closes the serial connection.
     *
     * @return void.
     */
    void closeSerial();

    /**
     * @brief Contains a list of all the available ports.
     *
     * @return Returns a std::vector<std::string> of all the available ports.
     */
    static std::vector<std::string> availablePorts();

    /**
     * @brief the Serial's destructor.
     */
    ~Serial();
};
#endif // WIN32