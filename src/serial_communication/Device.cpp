#ifdef WIN32
/* HOW TO USE IN MAIN CODE
    std::vector<std::string> ports = Serial::availablePorts();
    const char* port = ports[0].c_str();

    auto device = new Device();
    device->setPort(port);
    device->connect();
*/

#include "serial_communication/Device.hpp"
#include <iostream>

Device::Device() {

}

bool Device::connect() {
    if (!this->port) {
        std::cerr << "ERROR: A port has not been set for the device." << std::endl;
        return false;
    }

    std::unique_ptr<Serial> _device = std::make_unique<Serial>(this->port);

    std::cout << "Searching in progress";

    uint8_t count = 0;

    while (!_device->isConnected()) {
        Sleep(100);
        std::cout << this->port;
        _device = std::make_unique<Serial>(this->port);

        // If we havent connected after 50 attempts (5 seconds) then stop trying.
        if (++count == 50) {
            std::cerr << "ERROR: Unable to connect to Serial device." << std::endl;
            return false;
        }

    }

    std::cout << std::endl << "Connection established at port " << this->port << std::endl;

    this->device = std::move(_device);

    return true;
};

void Device::setPort(const char *_port) {
    this->port = _port;
};

const char* Device::getPort() {
    return port;
}

std::string Device::read() {
    std::string data;

    while (data.find('<') == std::string::npos) {
        char incomingData[255];
        device->readSerialPort(incomingData, 255);

        data += std::string(incomingData);
    }

    return data;
};

void Device::write(char _data[]) {
    device->writeSerialPort(_data, 255);
};

bool Device::isConnected() {
    return device->isConnected();
};
#endif