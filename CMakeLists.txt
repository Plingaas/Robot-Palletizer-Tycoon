cmake_minimum_required(VERSION 3.15)
project(RobotController)

set(CMAKE_CXX_STANDARD 17)

find_package(threepp CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)

file(COPY "${CMAKE_SOURCE_DIR}/resources/models" DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/bin/data)
add_executable(test main.cpp serial_communication/Serial.cpp serial_communication/Serial.h serial_communication/Device.cpp serial_communication/Device.h UI.cpp UI.h robot_arm/Robot.cpp robot_arm/Robot.h robot_arm/Joint.cpp robot_arm/Joint.h robot_arm/tools/IK.cpp robot_arm/tools/IK.h robot_arm/tools/PID.h App.cpp App.h Listener.cpp Listener.h helpers/LinkedList.h robot_arm/tools/Program.cpp robot_arm/tools/Program.h objects/ConveyorBelt.cpp objects/ConveyorBelt.h helpers/Helper.h helpers/Helper.cpp objects/EuroPallet.cpp objects/EuroPallet.h objects/items/Box.cpp objects/items/Box.h objects/items/Item.cpp objects/items/Item.h Game.cpp Game.h)
target_link_libraries(test PRIVATE threepp::threepp imgui::imgui)
