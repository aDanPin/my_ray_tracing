cmake_minimum_required(VERSION 3.10)

# set the project name
project(ray_tracing)

include_directories(include)
# add_subdirectory(src)

# add the executable
add_executable(render_scine main.cpp)
