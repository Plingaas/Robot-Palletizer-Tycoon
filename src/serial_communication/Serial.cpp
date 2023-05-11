//
// Code from https://github.com/manashmandal/SerialPort
//
// Contains all Serial communication functionality.
// Read() Write() Connect() etc..
//
// availablePorts() written by Peter
//

#include "serial_communication/Serial.hpp"
#include <iostream>

Serial::Serial(const char *portName) {
    this->connected = false;

    this->handler = CreateFileA(static_cast<LPCSTR>(portName),
                                GENERIC_READ | GENERIC_WRITE,
                                0,
                                NULL,
                                OPEN_EXISTING,
                                FILE_ATTRIBUTE_NORMAL,
                                NULL);
    if (this->handler == INVALID_HANDLE_VALUE) {
        if (GetLastError() == ERROR_FILE_NOT_FOUND) {
            std::cerr << "ERROR: Handle was not attached.Reason : " << portName << " not available\n";
        } else {
            std::cerr << "ERROR!!!\n";
        }
    } else {
        DCB dcbSerialParameters = {0};

        if (!GetCommState(this->handler, &dcbSerialParameters)) {
            std::cerr << "Failed to get current serial parameters\n";
        } else {
            dcbSerialParameters.BaudRate = CBR_115200;
            dcbSerialParameters.ByteSize = 8;
            dcbSerialParameters.StopBits = ONESTOPBIT;
            dcbSerialParameters.Parity = NOPARITY;
            dcbSerialParameters.fDtrControl = DTR_CONTROL_ENABLE;

            if (!SetCommState(handler, &dcbSerialParameters)) {
                std::cout << "ALERT: could not set serial port parameters\n";
            } else {
                this->connected = true;
                PurgeComm(this->handler, PURGE_RXCLEAR | PURGE_TXCLEAR);
                Sleep(ARDUINO_WAIT_TIME);
            }
        }
    }
}

Serial::~Serial() {
    if (this->connected) {
        this->connected = false;
        CloseHandle(this->handler);
    }
}


int Serial::readSerialPort(const char *buffer, unsigned int buf_size) {
    DWORD bytesRead{};
    unsigned int toRead = 0;

    ClearCommError(this->handler, &this->errors, &this->status);

    if (this->status.cbInQue > 0) {
        if (this->status.cbInQue > buf_size) {
            toRead = buf_size;
        } else {
            toRead = this->status.cbInQue;
        }
    }

    memset((void *) buffer, 0, buf_size);

    if (ReadFile(this->handler, (void *) buffer, toRead, &bytesRead, NULL)) {
        return bytesRead;
    }

    std::cout << "returning 0" << std::endl;
    return 0;
}

bool Serial::writeSerialPort(const char *buffer, unsigned int buf_size) {
    DWORD bytesSend;

    if (!WriteFile(this->handler, (void *) buffer, buf_size, &bytesSend, 0)) {
        ClearCommError(this->handler, &this->errors, &this->status);
        return false;
    }

    return true;
}

// Checking if serial port is connected
bool Serial::isConnected() {
    if (!ClearCommError(this->handler, &this->errors, &this->status)) {
        this->connected = false;
    }

    return this->connected;
}

void Serial::closeSerial() {
    CloseHandle(this->handler);
}

// Added functionality to search for available com ports
std::vector<std::string> Serial::availablePorts() {

    std::vector<std::string> ports;

    for (int i = 1; i <= 255; i++) {

        std::string portName = "\\\\.\\COM" + std::to_string(i);
        const char *port = portName.c_str();

        HANDLE handle = CreateFileA(static_cast<LPCSTR>(port),
                                    GENERIC_READ | GENERIC_WRITE,
                                    0,
                                    NULL,
                                    OPEN_EXISTING,
                                    FILE_ATTRIBUTE_NORMAL,
                                    NULL);

        if (GetLastError() != ERROR_FILE_NOT_FOUND) {
            ports.emplace_back(portName);
        }

        CloseHandle(handle);
    }

    return ports;
}