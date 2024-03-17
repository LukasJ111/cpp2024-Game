cmake_minimum_required(VERSION 3.27)
project(Miskas)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake_modules)
set(SDL2_PATH "C:/Dev/SDL2-2.30.1/x86_64-w64-mingw32")

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})


add_executable(Miskas main.cpp)
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARY})
