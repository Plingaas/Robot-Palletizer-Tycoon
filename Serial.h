#pragma once

#define ARDUINO_WAIT_TIME 2000
#define MAX_DATA_LENGTH 255

#include <windows.h>
#include <iostream>
#include <vector>
#include <stdio.h>
#include <iostream>
#include <string>

class Serial
{
private:
    HANDLE handler;
    bool connected;
    COMSTAT status;
    DWORD errors;

public:
    explicit Serial(const char *portName);
    ~Serial();

    int readSerialPort(const char *buffer, unsigned int buf_size);
    bool writeSerialPort(const char *buffer, unsigned int buf_size);
    bool isConnected();
    void closeSerial();
    static std::vector<std::string> availablePorts();
};