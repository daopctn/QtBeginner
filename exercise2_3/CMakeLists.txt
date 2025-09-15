cmake_minimum_required(VERSION 3.16)
project(QtBeginnerExercises VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets)

set(CMAKE_AUTOMOC ON)

set(SOURCES
    main.cpp
)

add_executable(exercise23 ${SOURCES})

target_link_libraries(exercise23 Qt6::Core Qt6::Widgets)

if(WIN32)
    set_property(TARGET exercise23 PROPERTY WIN32_EXECUTABLE TRUE)
endif()