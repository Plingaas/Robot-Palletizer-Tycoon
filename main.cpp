
#include "App.h"
#include "serial_communication/Device.h"
#include <thread>
#include <iostream>

int main() {

    int A = 0;
    int B = 0;
    int C = 0;
    char* port = nullptr;
    Device device;

    auto window = [&A, &B, &C, &port]()
    {
        run(&A, &B, &C, &port);
    };

    std::thread app_thread(window);

    auto serial_comm = [&A, &B, &C, &port, &device]()
    {

        while (port == nullptr)
        {

        }
        device.setPort(port);
        device.connect();

        while (device.isConnected()) {
            std::string data = device.read();

            int A_index = data.find('A');
            int B_index = data.find('B');
            int C_index = data.find('C');
            int end = data.find('<');

            A = std::stoi(data.substr(A_index + 1, B_index - A_index - 1));
            B = std::stoi(data.substr(B_index + 1, C_index - B_index - 1));
            C = std::stoi(data.substr(C_index + 1, end - C_index - 1));

        }


        /*
        PORTS = Serial::availablePorts();

        std::cout << "Available ports: " << PORTS.size() << std::endl;
        if (!PORTS.empty()) {
            for (const std::string& port : PORTS) {
                std::cout << port << std::endl;
            }

            std::cout << "Choose port " << std::endl;
            std::string port = R"(\\.\COM)";

            std::string input;
            std::cin >> input;
            port += input;

            const char* _port = port.c_str();





        }*/
    };

    std::thread serial_thread(serial_comm);

    app_thread.join();
    serial_thread.join();
}
