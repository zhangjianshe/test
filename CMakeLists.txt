cmake_minimum_required(VERSION 3.10)
project(zjs)

set(CMAKE_CXX_STANDARD 11)
set(SOURCE_FILES main.cpp;ScriptEngine.h ScriptBuffer.h)


find_package(Lua 5.3 REQUIRED)
include_directories(${LUA_INCLUDE_DIR})


message("   *** Lua include: ${LUA_INCLUDE_DIR}")
message("   *** Lua lib: ${LUA_LIBRARIES}")

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} ${LUA_LIBRARIES})