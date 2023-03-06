cmake_minimum_required(VERSION 3.15)
project(RobotController)

set(CMAKE_CXX_STANDARD 17)

find_package(threepp CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)

add_executable(test main.cpp serial_communication/Serial.cpp serial_communication/Serial.h serial_communication/Device.cpp serial_communication/Device.h UI.cpp UI.h robot_arm/Robot.cpp robot_arm/Robot.h robot_arm/Joint.cpp robot_arm/Joint.h robot_arm/tools/IK.cpp robot_arm/tools/IK.h App.cpp App.h Listener.cpp Listener.h robot_arm/tools/PID.cpp robot_arm/tools/PID.h)
target_link_libraries(test PRIVATE threepp::threepp imgui::imgui)
