cmake_minimum_required(VERSION 3.15)
project(Inventory-Game)

include_directories(include/)

find_package(SDL3 REQUIRED)

set(SDL3_ttf_DIR "C:/mingw64/x86_64-w64-mingw32/lib/cmake/SDL3_ttf")
find_package(SDL3_ttf REQUIRED)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin/build/)

add_executable(${PROJECT_NAME}
    src/main.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    SDL3
    SDL3_ttf
)
