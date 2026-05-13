cmake_minimum_required(VERSION 3.25)
project(CalculatorSDL C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Forza la build statica per tutto il progetto e le dipendenze
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)

include(FetchContent)

# Scarica SDL3
FetchContent_Declare(
    SDL3
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
    GIT_TAG main
)
set(SDL_SHARED OFF CACHE BOOL "" FORCE)
set(SDL_STATIC ON CACHE BOOL "" FORCE)

# Scarica SDL3_ttf
FetchContent_Declare(
    SDL3_ttf
    GIT_REPOSITORY https://github.com/libsdl-org/SDL_ttf.git
    GIT_TAG main
)
set(SDL3TTF_SHARED OFF CACHE BOOL "" FORCE)
set(SDL3TTF_STATIC ON CACHE BOOL "" FORCE)
set(SDL3TTF_VENDORED ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(SDL3 SDL3_ttf)

add_executable(CalculatorSDL
    src/main.c
    src/Button.c
    src/Util.c
    src/Calculator.c
)

# Aggiunge la directory include al path di ricerca
target_include_directories(CalculatorSDL PRIVATE include)

# Copia i font nella cartella di build
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/assets/fonts DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

# Linka le versioni statiche delle librerie
target_link_libraries(CalculatorSDL
    PRIVATE
        SDL3::SDL3-static
        SDL3_ttf::SDL3_ttf-static
)

set_target_properties(CalculatorSDL
    PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
)
