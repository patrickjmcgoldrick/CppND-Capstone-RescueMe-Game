cmake_minimum_required(VERSION 3.7)

add_definitions(-std=c++17)

set(CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS, "${CXX_FLAGS}")

project(SDL2Test)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
include_directories(${SDL2_IMAGE_INCLUDE_DIRS})
include_directories(src)

add_executable(RescueMe src/main.cpp src/game.cpp src/controller.cpp src/renderer.cpp src/snake.cpp src/actor.cpp src/patron.cpp src/lifeguard.cpp)
target_link_libraries(RescueMe ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})
