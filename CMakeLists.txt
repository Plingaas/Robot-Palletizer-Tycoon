cmake_minimum_required(VERSION 3.15)
project(RobotController)

set(CMAKE_CXX_STANDARD 17)

find_package(threepp CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)

# kanskje ditta e nokke feil med, d har med catch 2 å gjøre elns
add_executable(CI_test)
target_include_directories(CI_test PUBLIC "${CMAKE_SOURCE_DIR}/include")
#

include(FetchContent)
FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v2.13.8
)
FetchContent_MakeAvailable(Catch2)

enable_testing()
add_subdirectory(tests)

file(GLOB_RECURSE SOURCES "src/*.cpp")
include_directories(${CMAKE_SOURCE_DIR}/include)

file(COPY "${CMAKE_SOURCE_DIR}/resources/models" DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/bin/data)
add_executable(game ${SOURCES} main.cpp)
target_link_libraries(game PRIVATE threepp::threepp imgui::imgui)
