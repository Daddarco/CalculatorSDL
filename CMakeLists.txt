cmake_minimum_required(VERSION 3.25)
project(CalculatorSDL C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)

find_package(SDL3 REQUIRED)
find_package(SDL3_ttf REQUIRED)

add_executable(CalculatorSDL
    src/main.c
    assets/Button.c
)

target_include_directories(CalculatorSDL PRIVATE assets)

target_link_libraries(CalculatorSDL
    PRIVATE
        SDL3::SDL3
        SDL3_ttf::SDL3_ttf
)

set_target_properties(CalculatorSDL
    PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
)
