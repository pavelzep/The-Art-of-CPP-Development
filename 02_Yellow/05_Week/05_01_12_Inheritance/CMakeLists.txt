cmake_minimum_required(VERSION 3.0.0)
project(05_01_12_Inheritance VERSION 0.1.0 LANGUAGES CXX)

set(SOURCE_PATH src)
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

set(CMAKE_CXX_STANDARD 17)
#set(CMAKE_CXX_STANDARD 20)
#set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wsign-conversion")

add_executable(${PROJECT_NAME} 
    ${SOURCE_PATH}/main.cpp
    )