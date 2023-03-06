cmake_minimum_required(VERSION 3.5)

project(HighlightSlideNavigationBar LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(HighlightSlideNavigationBar main.cpp)

install(TARGETS HighlightSlideNavigationBar
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})