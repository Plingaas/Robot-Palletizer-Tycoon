cmake_minimum_required(VERSION 3.15)
project(RobotController)

set(CMAKE_CXX_STANDARD 17)

find_package(threepp CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)


add_executable(test main.cpp serial_communication/Serial.cpp serial_communication/Serial.h serial_communication/Device.cpp serial_communication/Device.h UI.cpp UI.h robot_arm/Robot.cpp robot_arm/Robot.h robot_arm/Joint.cpp robot_arm/Joint.h robot_arm/IK.cpp robot_arm/IK.h App.cpp App.h)
target_link_libraries(test PRIVATE threepp::threepp imgui::imgui)
