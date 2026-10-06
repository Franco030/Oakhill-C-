cmake_minimum_required(VERSION 3.10)
project(Oakhill CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Buscar SDL2
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(SDL2_ttf REQUIRED)

# Encontrar todos los archivos fuente (.cpp) de forma recursiva en la carpeta src
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Crear el ejecutable
add_executable(Oakhill ${SOURCES}
    include/utils/SDLPtrs.hpp)

target_include_directories(Oakhill PRIVATE 
    ${CMAKE_SOURCE_DIR}/include 
    ${SDL2_INCLUDE_DIRS}
)

target_link_libraries(Oakhill PRIVATE 
    SDL2::SDL2
    SDL2_image::SDL2_image 
    SDL2_mixer::SDL2_mixer 
    SDL2_ttf::SDL2_ttf
)