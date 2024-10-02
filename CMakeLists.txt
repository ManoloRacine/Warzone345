cmake_minimum_required(VERSION 3.25.1)
project(Warzone345)

set(CMAKE_CXX_STANDARD 20)

# Add source files and headers for the main executable
add_executable(Warzone345
    main.cpp
    src/Map/Map.h
    src/Map/Map.cpp
    src/Map/MapDriver.cpp
    src/Map/MapDriver.h
)

# Copy resource files (maps) to the build directory
file(COPY res/maps/Europe.txt res/maps/USA.txt res/maps/USAError.txt
    DESTINATION ${CMAKE_BINARY_DIR}/res/maps)
