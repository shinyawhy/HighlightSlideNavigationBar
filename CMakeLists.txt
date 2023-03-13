cmake_minimum_required(VERSION 3.5)

project(HighlightSlideNavigationBar LANGUAGES CXX)

include("${CMAKE_CURRENT_SOURCE_DIR}/CMakeLocals.cmake")

list(APPEND CMAKE_PREFIX_PATH ${QT_ENV})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE "Debug")

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5
    REQUIRED
    COMPONENTS Core Gui Widgets Charts NetWork
)
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/src")

file(GLOB_RECURSE SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
file(GLOB_RECURSE HEADER_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp" "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h")

set(PROJECT_SOURCES ${SOURCE_FILES})
set(PROJECT_HEADERS ${HEADER_FILES})

add_executable(${PROJECT_NAME}
    ${PROJECT_SOURCES}
    ${PROJECT_HEADERS})

target_link_libraries(${PROJECT_NAME}
    PUBLIC
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
    Qt5::Network
)


install(TARGETS HighlightSlideNavigationBar
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
