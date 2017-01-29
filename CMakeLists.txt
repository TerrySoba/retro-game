cmake_minimum_required(VERSION 3.5.1)

project(RetroGame)
set (CMAKE_CXX_STANDARD 14)


find_package(PNG REQUIRED)

add_definitions(${PNG_DEFINITIONS})

add_library(${PROJECT_NAME} SHARED
    src/retro_game.cpp
    src/game_base.cpp
    src/image.h
    src/png_image.h
    src/png_image.cpp
    src/exception.h
    src/exception.cpp
    src/rectangle.h
    src/rectangle.cpp
    src/animation.h
    src/mikmod_driver/drv_retro_game.c
    src/mikmod_driver/drv_retro_game.h
    src/mikmod_sound.cpp
    src/mikmod_sound.h
    3rd_party/fmt/format.cc
    3rd_party/fmt/format.h
    3rd_party/libretro/libretro.h)

INCLUDE_DIRECTORIES(
    ${PNG_INCLUDE_DIRS}
    3rd_party
    src
    #/home/yoshi252/program_sources/libmikmod-3.3.10-install/include)
    )

target_link_libraries(${PROJECT_NAME}
    ${PNG_LIBRARIES}
    mikmod
    physfs
    #/home/yoshi252/program_sources/libmikmod-3.3.10-install/lib/libmikmod.so.3.3.0)
    )


add_executable(${PROJECT_NAME}_testsuite
    3rd_party/catch/catch.hpp
    test/main.cpp
    test/rectangle_test.cpp)

target_link_libraries(${PROJECT_NAME}_testsuite
    ${PROJECT_NAME})
