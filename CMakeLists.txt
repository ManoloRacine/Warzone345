cmake_minimum_required(VERSION 3.25.1)
project(Warzone345)

#set(BOOST_ROOT "/usr")
#set(BOOST_INCLUDEDIR "/usr/include")
#set(BOOST_LIBRARYDIR "/usr/lib/x86_64-linux-gnu")

# Find Boost Libraries
#find_package(Boost 1.74.0 REQUIRED)

set(CMAKE_CXX_STANDARD 20)

# Include directories for header files
include_directories(
        ${PROJECT_SOURCE_DIR}/src
        ${PROJECT_SOURCE_DIR}/src/Cards
        ${PROJECT_SOURCE_DIR}/src/GameEngine
        ${PROJECT_SOURCE_DIR}/src/Map
        ${PROJECT_SOURCE_DIR}/src/Orders
        ${PROJECT_SOURCE_DIR}/src/Player
        ${PROJECT_SOURCE_DIR}/src/Logger
)

# Include Boost headers
#include_directories(${Boost_INCLUDE_DIRS})


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
        src/Command/Command.h
        src/Command/Command.cpp
        src/CommandProcessing/CommandProcessor.h
        src/CommandProcessing/CommandProcessor.cpp
        src/CommandProcessing/CommandProcessingDriver.cpp
        src/Logger/LogObserver.h
        src/Logger/LogObserver.cpp
)

# Link Boost libraries to your executable
#target_link_libraries(Warzone345 ${Boost_LIBRARIES})
target_link_libraries(Warzone345)

# Copy resource files (maps) to the build directory
file(COPY res/maps/africa.txt res/maps/europe.txt res/maps/usa.txt res/maps/usa_emptycontinent.txt res/maps/europe_notconnected.txt res/maps/africa_unconnectedsubgraph.txt
    DESTINATION ${CMAKE_BINARY_DIR}/res/maps)
