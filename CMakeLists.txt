cmake_minimum_required(VERSION 3.8)
project(Polynomial_Fighter)

set(CMAKE_CXX_STANDARD 17)

link_libraries(sfml-network sfml-audio sfml-graphics sfml-window sfml-system)

file(GLOB SOURCE_FILES "Polynomial-Fighter/*.cpp")

add_executable(Polynomial_Fighter ${SOURCE_FILES})