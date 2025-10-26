# based on https://github.com/SFML/cmake-sfml-project, sfml2 branch

cmake_minimum_required(VERSION 3.28)
project(Polynomial_Fighter LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

# link_libraries(sfml-network sfml-audio sfml-graphics sfml-window sfml-system)

file(GLOB SOURCE_FILES "Polynomial-Fighter/*.cpp")

add_executable(polynomial_fighter ${SOURCE_FILES})
target_link_libraries(polynomial_fighter PRIVATE sfml-graphics sfml-audio sfml-system sfml-window)
