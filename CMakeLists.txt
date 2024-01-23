cmake_minimum_required(VERSION 3.16)
project(smc_cppserial_lib LANGUAGES CXX)



include_directories(include)
add_executable( motor_control examples/motor_control.cpp )
target_link_libraries( motor_control serial )

