cmake_minimum_required(VERSION 3.25.1)
project(Warzone345)

set(CMAKE_CXX_STANDARD 20)

add_executable(Warzone345 main.cpp
        GameEngine.h
        GameEngine.cpp
        GameEngineDriver.cpp)
