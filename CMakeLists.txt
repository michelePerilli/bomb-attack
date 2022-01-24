cmake_minimum_required(VERSION 3.10)
project(bomb-attack)

set(CMAKE_CXX_STANDARD 14)
cmake_policy(SET CMP0074 NEW)

add_executable(bomb-attack
        source/Bomb.h
        source/Casa.h
        source/Collider.h
        source/main.cpp)

install(TARGETS ${PROJECT_NAME} DESTINATION source)

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR "D:/dev/c/.libs/SFML-2.5.1/lib/cmake/SFML")
# Detect and add SFML
find_package(SFML 2.5.1 COMPONENTS system window graphics audio network REQUIRED)

include_directories(../.libs/SFML-2.5.1/include)

target_link_libraries(bomb-attack sfml-system sfml-window sfml-graphics sfml-audio sfml-network)
