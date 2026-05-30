cmake_minimum_required(VERSION 3.16)
project(main LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

add_executable(main
	testing/main.cpp
	${CMAKE_SOURCE_DIR}/include/glad/src/glad.c
)

target_include_directories(main PRIVATE
	${CMAKE_SOURCE_DIR}/include/glad/include
	${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(main PRIVATE
	glfw
	OpenGL::GL
	${CMAKE_DL_LIBS}
)

target_compile_definitions(main PRIVATE
	SHADER_DIR="${CMAKE_SOURCE_DIR}/src/rendering/graphics/shaders/glsl_files"
)
