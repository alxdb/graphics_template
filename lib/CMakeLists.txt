find_package(glfw3 3.2 REQUIRED)
find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)
find_package(spdlog REQUIRED)

add_subdirectory(oogl)

add_library(lib Display.cpp Display.hpp)
target_include_directories(lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(lib oogl glfw spdlog::spdlog GLEW::glew OpenGL::GL)
