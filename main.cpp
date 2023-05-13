#include "Game.hpp"
#include "Visualization.hpp"
#include "serial_communication/Device.hpp"
#include <thread>
#include <iostream>

int main() {

    std::array<int, 3> serialData{};

    char* port = nullptr;


    // Main application
    auto window = [&serialData, &port]()
    {

        bool mode = false;
        std::cout << "Enter 0 to play the game.\nEnter 1 to open the visualization tool.\n";
        std::cin >> mode;

        if (mode) {
            Visualization viz;
            viz.runVisualization(serialData, &port);
        } else {
            Game game;
            game.runGame();
        }

        exit(0);

    };

    std::thread app_thread(window);

#ifdef WIN32
    Device device;
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

    serial_thread.join();
//#endif // WIN32
    app_thread.join();


}
#endif