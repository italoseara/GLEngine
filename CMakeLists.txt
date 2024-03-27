cmake_minimum_required(VERSION 3.5)
project(myproject VERSION 0.1.0 LANGUAGES C CXX)
cmake_policy(SET CMP0072 NEW)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenGL REQUIRED)

add_executable(myproject src/main.cpp)

target_link_libraries(myproject glfw)
target_include_directories(myproject PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)