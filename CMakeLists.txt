cmake_minimum_required(VERSION 3.5.1)

project(RetroGame)
set (CMAKE_CXX_STANDARD 14)


find_package(PNG REQUIRED)

add_definitions(${PNG_DEFINITIONS})

add_library(${PROJECT_NAME} SHARED
    retro_game.cpp
    game_base.cpp
    image.h
    png_image.h
    png_image.cpp
    exception.h
    exception.cpp
    fmt/format.cc
    fmt/format.h)

INCLUDE_DIRECTORIES(
    ${PNG_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME}
    ${PNG_LIBRARIES})
