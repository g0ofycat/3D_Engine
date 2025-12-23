cmake_minimum_required(VERSION 3.16)
project(main LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(main
    testing/main.cpp
    C:/winlibs-x86_64-cpp/mingw64/include/c++/15.2.0/glad/src/glad.c
)

target_include_directories(main PRIVATE
    C:/winlibs-x86_64-cpp/mingw64/include/c++/15.2.0/glad/include
    C:/glfw/glfw-3.4.bin.WIN64/include
)

target_link_directories(main PRIVATE
    C:/glfw/glfw-3.4.bin.WIN64/lib-mingw-w64
)

target_link_libraries(main
    glfw3
    opengl32
    gdi32
    user32
    kernel32
)

target_link_options(main PRIVATE
    -static-libgcc
    -static-libstdc++
)

add_custom_target(run
    COMMAND $<TARGET_FILE:main>
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    DEPENDS main
    COMMENT "Building and running main..."
)