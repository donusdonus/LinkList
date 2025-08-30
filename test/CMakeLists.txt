cmake_minimum_required(VERSION 3.14)
project(AppExample)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_C_STANDARD 11)
set(CMAKE_BUILD_TYPE Debug)

#include(FetchContent)
#FetchContent_Declare(
#  freertos
#  GIT_REPOSITORY https://github.com/FreeRTOS/FreeRTOS-Kernel.git
#  GIT_TAG main
#  UPDATE_DISCONNECTED TRUE
#)
#FetchContent_MakeAvailable(freertos)

# ✅ เพิ่มไลบรารี mountkit
add_subdirectory(../ ${CMAKE_CURRENT_BINARY_DIR}/LinkList)

# ✅ สร้าง executable
add_executable(app main.cpp)


# ✅ link libraries
target_link_libraries(app
  PRIVATE
  LinkList
)