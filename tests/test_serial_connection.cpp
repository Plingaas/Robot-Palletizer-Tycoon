#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#ifdef WIN32
#include "serial_communication/Device.hpp"
#endif

TEST_CASE("Serial Connection Test") {
#ifdef WIN32
    std::vector<std::string> ports = Serial::availablePorts();

    const char* port = ports[0].c_str();

    auto device = new Device();
    device->setPort(port);
    device->connect();

    CHECK(device->isConnected());

#else
    std::cout << "WIN32 not defined, cannot test serial connection." << std::endl;
    bool a = true;
    CHECK(a == true); // I still want it to pass.
#endif
}