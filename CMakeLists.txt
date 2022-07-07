cmake_minimum_required(VERSION 3.0)

project(AstraPowerSettings)

set(PRINT_VERSION_MAJOR 0)
set(PRINT_VERSION_MINOR 1)
set(PRINT_VERSION_PATCH 0)
set(PRINT_VERSION_TWEAK 0)
set(PRINT_VERSION ${PRINT_VERSION_MAJOR}.${PRINT_VERSION_MINOR}.${PRINT_VERSION_PATCH}.${PRINT_VERSION_TWEAK})
set(PRINT_VERSION_STRING "v${PRINT_VERSION}")

set(CMAKE_CXX_STANDARD 11)

add_library(Commons STATIC
        ${CMAKE_CURRENT_SOURCE_DIR}/Commons/Terminal.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Commons/Logger.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Commons/Utils.cpp
        )

target_include_directories(Commons PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Commons/>
        $<INSTALL_INTERFACE:include>
        )

add_executable(${PROJECT_NAME} demo/main.cpp)

target_link_libraries(${PROJECT_NAME} Commons)

install(TARGETS ${PROJECT_NAME} DESTINATION bin)
include(CPackConfig.cmake)
