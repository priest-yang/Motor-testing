cmake_minimum_required(VERSION 3.10.2)
project(UnitreeMotorSDK_M80106)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O3")

include_directories("include/")
link_directories(
    lib/
)

#example
add_executable(motorctrl example/main.cpp
        example/preprogrammed.cpp
        example/preprogrammed.h)
target_link_libraries(motorctrl libUnitreeMotorSDK_M80106_Linux64.so)

#example
add_executable(stop example/stop.cpp
        example/preprogrammed.cpp
        example/preprogrammed.h)
target_link_libraries(stop libUnitreeMotorSDK_M80106_Linux64.so)


add_executable(PID_helper example/PID_helper.cpp
	example/preprogrammed.cpp
        example/preprogrammed.h)
target_link_libraries(PID_helper libUnitreeMotorSDK_M80106_Linux64.so)
