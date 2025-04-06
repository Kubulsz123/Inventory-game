cmake_minimum_required(VERSION 3.15)
project(Inventory-Game)

include_directories(include/)
find_package(SDL3 REQUIRED)
find_package(SDL3_ttf REQUIRED)
find_package(SDL3_image REQUIRED CONFIG)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin/build/)

add_executable(${PROJECT_NAME}
    src/main.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    SDL3
    SDL3_ttf
    SDL3_image
)
