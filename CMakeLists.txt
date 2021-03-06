cmake_minimum_required(VERSION 3.1.3)

if(CMAKE_BUILD_TYPE STREQUAL "Release" OR CMAKE_BUILD_TYPE STREQUAL "Debug")
else()
        message("CMAKE_BUILD_TYPE should to be set to Release or Debug, assuming Release for now.")
        set(CMAKE_BUILD_TYPE "Release")
endif()

project(RetroGame)
set (CMAKE_CXX_STANDARD 11)

if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
  # Update if necessary
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -Werror")
endif()

set(USE_MIKMOD true CACHE BOOL "Use mikmod to play music and sounds.")

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR})

if (USE_MIKMOD)
    include (mikmod.cmake)
endif(USE_MIKMOD)

include (boost.cmake)
include (GenerateExportHeader)


if (${CMAKE_CURRENT_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
    add_custom_target(package_game_assets
        COMMAND echo "In source build, so nothing to copy."
        )
else()
    add_custom_target(package_game_assets
        COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_CURRENT_SOURCE_DIR}/assets" "${CMAKE_BINARY_DIR}/assets"
        )
endif()

INCLUDE_DIRECTORIES(
    ${Boost_INCLUDE_DIRS}
    ${MIKMOD_INCLUDE_DIR}
    ${CMAKE_BINARY_DIR}
    3rd_party
    src
    )


set(${PROJECT_NAME}_SOURCES)
if(USE_MIKMOD)
    # If we use mikmod add sources
    list(APPEND ${PROJECT_NAME}_SOURCES
        src/mikmod_sound.cpp
        src/mikmod_sound.h
        src/mikmod_driver/drv_retro_game.c
        src/mikmod_driver/drv_retro_game.h
        )
else (USE_MIKMOD)
    # If mikmod is not used build dummy implementation
    list(APPEND ${PROJECT_NAME}_SOURCES
        src/mikmod_sound_dummy.cpp
        src/mikmod_sound.h
        )
endif(USE_MIKMOD)


list(APPEND ${PROJECT_NAME}_SOURCES
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
    src/animation.cpp
    src/gfx_object.h
    src/actor.h
    src/actors/enemy_ship.h
    src/actors/enemy_ship.cpp
    src/actors/player_ship.h
    src/actors/player_ship.cpp
    src/actors/bullet.h
    src/actors/bullet.cpp
    src/input_listener.h
    src/engine_access.h
    src/gfx_engine.h
    src/gfx_engine.cpp
    src/paint_surface.h
    src/paint_surface.cpp
    src/decode_utf8.h
    src/decode_utf8.cpp
    src/texture_font.h
    src/texture_font.cpp
    src/memory_image.h
    src/memory_image.cpp
    src/compare_image.h
    src/compare_image.cpp
    3rd_party/fmt/format.cc
    3rd_party/fmt/format.h
    3rd_party/libretro/libretro.h
    3rd_party/lodepng/lodepng.cpp
    )


add_library(${PROJECT_NAME} SHARED
    ${${PROJECT_NAME}_SOURCES}
    )

GENERATE_EXPORT_HEADER(${PROJECT_NAME})
	


target_link_libraries(${PROJECT_NAME}
    ${Boost_LIBRARIES}
    ${MIKMOD_LIBRARY}
    )

add_executable(${PROJECT_NAME}_testsuite
    3rd_party/catch/catch.hpp
    test/main.h
    test/main.cpp
    test/rectangle_test.cpp
    test/png_image_test.cpp
    test/mikmod_sound_test.cpp
    test/animation_test.cpp
    test/compare_image_test.cpp
    test/paint_surface_test.cpp)

# Run testsuite
add_custom_target(run_tests
    COMMAND ${PROJECT_NAME}_testsuite -r junit -o unit_test.xml -- --test-data-dir=${CMAKE_SOURCE_DIR}/test/test_data)

target_link_libraries(${PROJECT_NAME}_testsuite
    ${PROJECT_NAME})

add_dependencies(${PROJECT_NAME}
    package_game_assets)

add_subdirectory(doxygen)


if (WIN32)
    set(WINDOWS_PACKAGE_DIR "${CMAKE_BINARY_DIR}/windows_package")

    add_custom_target(create_windows_zip
        COMMAND mkdir -p "${WINDOWS_PACKAGE_DIR}"
        COMMAND cp "${CMAKE_BINARY_DIR}/libRetroGame.dll" "${WINDOWS_PACKAGE_DIR}"
        COMMAND cp "${CMAKE_BINARY_DIR}/RetroGame_testsuite.exe" "${WINDOWS_PACKAGE_DIR}"
        COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_CURRENT_SOURCE_DIR}/assets" "${WINDOWS_PACKAGE_DIR}/assets"
        COMMAND bash "${CMAKE_CURRENT_SOURCE_DIR}/copy_dependencies.sh" "${CMAKE_BINARY_DIR}/libRetroGame.dll" "${WINDOWS_PACKAGE_DIR}" "/mingw64"
        COMMAND ${CMAKE_COMMAND} -E tar "cf" ${CMAKE_BINARY_DIR}/retro-game.zip --format=zip ${WINDOWS_PACKAGE_DIR}
    )

    add_dependencies(create_windows_zip
        ${PROJECT_NAME}
        ${PROJECT_NAME}_testsuite)
		
endif(WIN32)

