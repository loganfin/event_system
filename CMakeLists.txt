cmake_minimum_required(VERSION 3.30)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_TYPE Debug)

project(event_system LANGUAGES C CXX)

add_executable(${PROJECT_NAME}
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
    #${CMAKE_CURRENT_SOURCE_DIR}/src/gpt.cpp
)

target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/lib)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        es
)

