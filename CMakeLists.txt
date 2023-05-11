cmake_minimum_required(VERSION 3.15)
project(RobotController)

set(CMAKE_CXX_STANDARD 17)

find_package(threepp CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)

file(GLOB_RECURSE SOURCES "src/*.cpp")
include_directories(${CMAKE_SOURCE_DIR}/include)

file(COPY "${CMAKE_SOURCE_DIR}/resources/models" DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/bin/data)
add_executable(test ${SOURCES} main.cpp Game.hpp Game.cpp src/listener/Listener.cpp)
target_link_libraries(test PRIVATE threepp::threepp imgui::imgui)
