#ifdef WIN32
#define CATCH_CONFIG_MAIN
#include "serial_communication/Device.hpp"
#include <catch2/catch.hpp>

TEST_CASE("Serial Connection Test") {
    std::vector<std::string> ports = Serial::availablePorts();

    const char* port = ports[0].c_str();

    auto device = new Device();
    device->setPort(port);
    device->connect();

    CHECK(device->isConnected());
}

#endif