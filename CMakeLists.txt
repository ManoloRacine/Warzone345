cmake_minimum_required(VERSION 3.25.1)
project(Warzone345)

set(CMAKE_CXX_STANDARD 20)

add_executable(Warzone345 main.cpp
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
)

