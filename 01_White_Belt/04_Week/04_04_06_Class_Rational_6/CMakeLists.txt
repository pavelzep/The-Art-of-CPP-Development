cmake_minimum_required(VERSION 3.0.0)
project(04_04_06_Class_Rational_6 VERSION 0.1.0)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
set(SOURCE_PATH src)

add_executable(${PROJECT_NAME} ${SOURCE_PATH}/main.cpp)