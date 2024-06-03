cmake_minimum_required(VERSION 3.5)

project(guiness
    VERSION 0.1
    DESCRIPTION "A Nes emulator"
)

find_library(NCURSES_LIB ncurses REQUIRED)
find_library(SDL2_LIB SDL2 REQUIRED)

add_executable(guiness
    main.cpp 
    debugger.cpp 
    logger.cpp
    bus.cpp
    wram.cpp
    dummy_device.cpp
    config.cpp
    video.cpp
    debugger.hpp
    logger.hpp
    bus.hpp
    dummy_device.hpp
    wram.hpp
    config.hpp
    video.hpp
)

target_link_libraries(guiness PUBLIC ${NCURSES_LIB})
target_link_libraries(guiness PUBLIC ${SDL2_LIB})

add_custom_target(run "guiness")
add_dependencies(run guiness)