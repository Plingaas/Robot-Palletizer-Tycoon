
#include "Game.hpp"
#include "serial_communication/Device.hpp"
#include <thread>
#include <iostream>

int main() {

    // Variables for storing serial data.
    int A = 0;
    int B = 0;
    int C = 0;

    std::array<int, 3> serialData{};

    char* port = nullptr;
    Device device;

    // Main application
    auto window = [&serialData, &port]()
    {
        Game game;
        game.run(&serialData, &port);
    };

    std::thread app_thread(window);

    auto serial_comm = [&serialData, &port, &device]()
    {

        while (port == nullptr)
        {
            // Sleep to free the CPU
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
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

            serialData[0] = std::stoi(data.substr(A_index + 1, B_index - A_index - 1));
            serialData[1] = std::stoi(data.substr(B_index + 1, C_index - B_index - 1));
            serialData[2] = std::stoi(data.substr(C_index + 1, end - C_index - 1));

        }
        
    };

    std::thread serial_thread(serial_comm);

    app_thread.join();
    serial_thread.join();
}
