cmake_minimum_required(VERSION 3.10)

# set the project name
project(ray_tracing)

include_directories(include)
# add_subdirectory(src)

# add the executable
find_package(OpenMP REQUIRED)
add_executable(render_scine main.cpp)
target_link_libraries(render_scine PRIVATE OpenMP::OpenMP_CXX)
