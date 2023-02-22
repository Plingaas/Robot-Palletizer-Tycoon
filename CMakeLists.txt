cmake_minimum_required(VERSION 3.15)
project(RobotController)

set(CMAKE_CXX_STANDARD 17)

find_package(threepp CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)

add_executable(test main.cpp Serial.cpp Serial.h Device.cpp Device.h UI.cpp UI.h RobotArm/Robot.cpp RobotArm/Robot.h RobotArm/Joint.cpp RobotArm/Joint.h RobotArm/IK.cpp RobotArm/IK.h App.cpp App.h)
target_link_libraries(test PRIVATE threepp::threepp imgui::imgui)
