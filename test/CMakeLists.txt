cmake_minimum_required(VERSION 3.14)
project(LINKLIST)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_C_STANDARD 11)
set(CMAKE_BUILD_TYPE Debug)

add_subdirectory(../ ${CMAKE_CURRENT_BINARY_DIR}/LINKLIST)


add_executable(app main.cpp)


# ✅ link libraries
target_link_libraries(app
  PRIVATE
  Linklist
)
