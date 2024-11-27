cmake_minimum_required(VERSION 3.24)
project(bpc-pc1t-snake-new C)

set(CMAKE_C_STANDARD 11)

# Dependencies
include(FetchContent)

set(RAYLIB_VERSION 5.5)
FetchContent_Declare(
    raylib
    URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
    FIND_PACKAGE_ARGS ${RAYLIB_VERSION}
)
set(BUILD_EXAMPLES OFF CACHE INTERNAL "")
FetchContent_MakeAvailable(raylib)

# Our Project
set(SOURCE_FILES
	main.c
    include/base.h
    include/fruitArray.h
    include/inputBuffer.h
    include/point.h
    include/snake.h
    include/statFile.h
    src/fruitArray.c
    src/inputBuffer.c
    src/snake.c
    src/statFile.c
)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} raylib)


# Checks if OSX and links appropriate frameworks (Only required on MacOS)
if (APPLE)
    target_link_libraries(${PROJECT_NAME} "-framework IOKit")
    target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif()