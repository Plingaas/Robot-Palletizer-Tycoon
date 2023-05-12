find_package(threepp CONFIG REQUIRED)

add_executable(test_serial_connection test_serial_connection.cpp ../src/serial_communication/Device.cpp ../src/serial_communication/Serial.cpp)
add_test(NAME test_serial_connection COMMAND test_serial_connection)
target_link_libraries(test_serial_connection PUBLIC Catch2::Catch2 threepp::threepp)
target_include_directories(test_serial_connection PUBLIC "${CMAKE_SOURCE_DIR}/include")

add_executable(test_conveyor test_conveyor.cpp ../src/objects/ConveyorBelt.cpp ../src/objects/items/Box.cpp ../src/helpers/Helper.cpp)
add_test(NAME test_conveyor COMMAND test_conveyor)
target_link_libraries(test_conveyor PUBLIC Catch2::Catch2 threepp::threepp)
target_include_directories(test_conveyor PUBLIC "${CMAKE_SOURCE_DIR}/include")