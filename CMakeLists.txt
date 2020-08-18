cmake_minimum_required(VERSION 3.17)
project(graphics_template_project)
set(CMAKE_CXX_STANDARD 17)

add_subdirectory(lib)

add_executable(main main.cpp)
target_link_libraries(main lib)

file(GLOB_RECURSE RESOURCES CONFIGURE_DEPENDS resources/*)
add_custom_command(TARGET main POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E make_directory
  $<TARGET_FILE_DIR:main>/resources
)
add_custom_command(TARGET main POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_if_different
  ${RESOURCES}
  $<TARGET_FILE_DIR:main>/resources
)
