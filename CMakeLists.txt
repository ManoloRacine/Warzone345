cmake_minimum_required(VERSION 3.25.1)
project(Warzone345)

set(CMAKE_CXX_STANDARD 20)

# Include directories for header files
include_directories(
        ${PROJECT_SOURCE_DIR}/src
        ${PROJECT_SOURCE_DIR}/src/Cards
        ${PROJECT_SOURCE_DIR}/src/GameEngine
        ${PROJECT_SOURCE_DIR}/src/Map
        ${PROJECT_SOURCE_DIR}/src/Orders
        ${PROJECT_SOURCE_DIR}/src/Player
)

# Add source files for the main executable
add_executable(Warzone345
        main.cpp
        src/Cards/Cards.cpp
        src/Cards/CardsDriver.cpp
        src/GameEngine/GameEngine.cpp
        src/GameEngine/GameEngineDriver.cpp
        src/Map/Map.cpp
        src/Map/MapDriver.cpp
        src/Orders/Order.cpp
        src/Orders/OrderDriver.cpp
        src/Player/Player.cpp
        src/Player/PlayerDriver.cpp
)

# Copy resource files (maps) to the build directory
file(COPY res/maps/Africa.txt res/maps/Europe.txt res/maps/USA.txt res/maps/USA_EmptyContinent.txt res/maps/Europe_NotConnected.txt res/maps/Africa_UnconnectedSubGraph.txt
    DESTINATION ${CMAKE_BINARY_DIR}/res/maps)
