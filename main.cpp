
#include "App.h"
#include "serial_communication/Device.h"
#include <thread>
#include <iostream>

int main() {

    // Variables for storing serial data.
    int A = 0;
    int B = 0;
    int C = 0;

    char* port = nullptr;
    Device device;

    // Main application
    auto window = [&A, &B, &C, &port]()
    {
        run(&A, &B, &C, &port);
    };

    std::thread app_thread(window);

    auto serial_comm = [&A, &B, &C, &port, &device]()
    {

        while (port == nullptr)
        {
            std::cout << "";
        }

        device.setPort(port);
        device.connect();

        while (device.isConnected()) {

            // Obtain data from string
            std::string data = device.read();

            int A_index = data.find('A');
            int B_index = data.find('B');
            int C_index = data.find('C');
            int end = data.find('<');

            A = std::stoi(data.substr(A_index + 1, B_index - A_index - 1));
            B = std::stoi(data.substr(B_index + 1, C_index - B_index - 1));
            C = std::stoi(data.substr(C_index + 1, end - C_index - 1));

        }
        
    };

    std::thread serial_thread(serial_comm);

    app_thread.join();
    serial_thread.join();
}
