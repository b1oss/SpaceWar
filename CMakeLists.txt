cmake_minimum_required(VERSION 3.16)

project(SpaceWar VERSION 1.0  LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Release>:Release>")
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

# SFML add_directory
Set(BUILD_SHARED_LIBS OFF CACHE BOOL "Build shared libraries" FORCE)
Set(SFML_STATIC_LIBRARIES ON CACHE BOOL "Build SFML static libraries" FORCE)

add_subdirectory(thirdparty/SFML EXCLUDE_FROM_ALL)


include_directories(${PROJECT_SOURCE_DIR}/include)

file(GLOB_RECURSE CPP_SOURCES ${PROJECT_SOURCE_DIR}/src/*.cpp)

set(SOURCES ${CPP_SOURCES})

add_executable(${PROJECT_NAME} ${SOURCES})

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
    SFML::Graphics
    SFML::Window
    SFML::System
    SFML::Audio
)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets
        $<TARGET_FILE_DIR:${PROJECT_NAME}>/assets
)
