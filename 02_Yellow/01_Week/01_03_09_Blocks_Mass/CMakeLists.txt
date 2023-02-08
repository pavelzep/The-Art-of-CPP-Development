cmake_minimum_required(VERSION 3.0.0)
project(01_03_09_Blocks_Mass VERSION 0.1.0)

set(SOURCE_PATH src)
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

add_executable(${PROJECT_NAME} ${SOURCE_PATH}/main.cpp)