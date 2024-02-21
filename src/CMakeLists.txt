cmake_minimum_required(VERSION 3.2)

project(guiness
    VERSION 0.1
    DESCRIPTION "A Nes emulator"
)

find_library(NCURSES_LIB ncurses)

add_executable(guiness
    main.cpp 
    debugger.cpp 
    logger.cpp
    bus.cpp
    dummy_device.cpp
    debugger.hpp
    logger.hpp
    bus.hpp
    dummy_device.hpp
)

target_link_libraries(guiness PUBLIC "${NCURSES_LIB}")

add_custom_target(run "guiness")
add_dependencies(run guiness)