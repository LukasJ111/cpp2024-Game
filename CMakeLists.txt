cmake_minimum_required(VERSION 3.27)
project(Miskas)

set(CMAKE_CXX_STANDARD 17)

find_package(SDL2 REQUIRED CONFIG)
find_package(SDL2_image REQUIRED CONFIG)


add_executable(Miskas main.cpp
        ResourceManagement/BaseResource.h
        ResourceManagement/AssetManager.cpp
        ResourceManagement/AssetManager.h
        ResourceManagement/TextureResource.cpp
        ResourceManagement/TextureResource.h)

target_link_libraries(Miskas PRIVATE SDL2::SDL2 SDL2_image::SDL2_image)