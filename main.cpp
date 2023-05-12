
#include "Game.hpp"
#include "serial_communication/Device.hpp"
#include <thread>
#include <iostream>

int main() {

    std::array<int, 3> serialData{};

    char* port = nullptr;
    Device device;

    // Main application
    auto window = [&serialData, &port]()
    {
        Game game;

        bool mode = false;
        std::cout << "Enter 0 to play the game.\nEnter 1 to open the visualization tool.\n";
        std::cin >> mode;

        if (mode)
            game.runVisualization(&serialData, &port);
        else
            game.runGame();
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

            int A_index = data.find('A') + 1;
            int B_index = data.find('B') + 1;
            int C_index = data.find('C') + 1;
            int end = data.find('<');

            serialData[0] = std::stoi(data.substr(A_index, B_index - A_index));
            serialData[1] = std::stoi(data.substr(B_index, C_index - B_index));
            serialData[2] = std::stoi(data.substr(C_index, end - C_index));
        }
    };

    std::thread serial_thread(serial_comm);

    app_thread.join();
    serial_thread.join();

}
