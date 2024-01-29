cmake_minimum_required(VERSION 3.0.0)
project(02_02_01_LoadFromIni VERSION 0.1.0 LANGUAGES CXX)

set(SOURCE_PATH src)
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

set(CMAKE_CXX_STANDARD 17)
#set(CMAKE_CXX_STANDARD 20)
#set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wsign-conversion")

add_executable(${PROJECT_NAME} 
    ${SOURCE_PATH}/main.cpp
    ${SOURCE_PATH}/ini.cpp
    # ${SOURCE_PATH}/spending.cpp
    # ${SOURCE_PATH}/solution.cpp
    )