cmake_minimum_required(VERSION 3.1.3)

project(RetroGame)
set (CMAKE_CXX_STANDARD 14)


find_package(PNG REQUIRED)


add_custom_target(package_game_assets
    COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_CURRENT_SOURCE_DIR}/assets" "${CMAKE_BINARY_DIR}/assets"
    )

add_definitions(${PNG_DEFINITIONS})

add_library(${PROJECT_NAME} SHARED
    src/libretro_interface.cpp
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
    src/gfx_object.h
    src/actor.h
    src/enemy_ship.h
    src/enemy_ship.cpp
    src/player_ship.h
    src/player_ship.cpp
    src/input_listener.h
    3rd_party/fmt/format.cc
    3rd_party/fmt/format.h
    3rd_party/libretro/libretro.h)

INCLUDE_DIRECTORIES(
    ${PNG_INCLUDE_DIRS}
    3rd_party
    src
    )

target_link_libraries(${PROJECT_NAME}
    ${PNG_LIBRARIES}
    mikmod
    )

add_executable(${PROJECT_NAME}_testsuite
    3rd_party/catch/catch.hpp
    test/main.cpp
    test/rectangle_test.cpp)

target_link_libraries(${PROJECT_NAME}_testsuite
    ${PROJECT_NAME})

add_dependencies(${PROJECT_NAME}
    package_game_assets)

add_subdirectory(doxygen)
