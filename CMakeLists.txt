cmake_minimum_required(VERSION 3.25.1)
project(Warzone345)

set(CMAKE_CXX_STANDARD 20)

#Main executable
add_executable(Warzone345 main.cpp)

#MapDriver executable
add_executable(MapDriver src/Map/MapDriver.cpp src/Map/Map.cpp)


add_custom_target(run_mapdriver
    COMMAND MapDriver ${CMAKE_SOURCE_DIR}/res/maps/USA.txt
    DEPENDS MapDriver
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/src/Map
    COMMENT "Running MapDriver..."
)
