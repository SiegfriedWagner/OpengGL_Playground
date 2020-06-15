# Projects Settings
cmake_minimum_required (VERSION 3.1)
project (opengl-skeleton)

# The main executable
add_executable(main
   src/Utils.hpp
   src/Utils.cpp
   src/Window.hpp
   src/Window.cpp
   src/OpenGLApp.hpp
   src/OpenGLApp.cpp
   src/Shader.hpp
   src/Shader.cpp
   src/Wektor.hpp
   src/Matrix.hpp
   src/MacierzGL.hpp
   src/MacierzGL.cpp
   src/Vertex.hpp
   src/Actor.hpp
   src/Actor.cpp
   src/Square.hpp
   src/Square.cpp
   src/Cuboid.hpp
   src/Cuboid.cpp
   src/main.cpp

)
set_property(TARGET main PROPERTY CXX_STANDARD 11)
target_compile_options(main PRIVATE -Wall)

# glfw
add_subdirectory(lib/glfw EXCLUDE_FROM_ALL)
target_link_libraries(main PRIVATE glfw)

# glew
add_definitions(-DGLEW_STATIC)
add_subdirectory(lib/glew EXCLUDE_FROM_ALL)
target_link_libraries(main PRIVATE libglew_static)

# glm
add_subdirectory(lib/glm EXCLUDE_FROM_ALL)
target_link_libraries(main PRIVATE glm)

#copy shaders
file(COPY shaders DESTINATION ${CMAKE_BINARY_DIR})