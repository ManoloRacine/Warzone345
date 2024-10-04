cmake_minimum_required(VERSION 3.25.1)
project(Warzone345)

set(CMAKE_CXX_STANDARD 20)

# Add source files and headers for the main executable
add_executable(Warzone345
    main.cpp
    src/Cards/Cards.h
    src/Cards/Cards.cpp
    src/Cards/CardsDriver.cpp
    src/GameEngine/GameEngine.h
    src/GameEngine/GameEngine.cpp
    src/GameEngine/GameEngineDriver.cpp
    src/Map/Map.h
    src/Map/Map.cpp
    src/Map/MapDriver.cpp
    src/Map/MapDriver.h
    src/Orders/Order.h
    src/Orders/Order.cpp
    src/Orders/OrderDriver.h
    src/Orders/OrderDriver.cpp
    src/Orders/Order.cpp
)

# Copy resource files (maps) to the build directory
file(COPY res/maps/Africa.txt res/maps/Europe.txt res/maps/USA.txt res/maps/USA_EmptyContinent.txt res/maps/Europe_NotConnected.txt res/maps/Africa_UnconnectedSubGraph.txt
    DESTINATION ${CMAKE_BINARY_DIR}/res/maps)
