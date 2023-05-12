find_package(threepp CONFIG REQUIRED)

add_executable(test_robot test_robot.cpp)
add_test(NAME test_robot COMMAND test_robot)
target_link_libraries(test_robot PUBLIC Catch2::Catch2 threepp::threepp)
target_include_directories(test_robot PUBLIC "${CMAKE_SOURCE_DIR}/include")

