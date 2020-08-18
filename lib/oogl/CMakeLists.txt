add_library(oogl oogl.hpp Buffer.hpp Program.hpp Program.cpp VertexArray.hpp VertexArray.cpp)
target_link_libraries(oogl GLEW::glew)
