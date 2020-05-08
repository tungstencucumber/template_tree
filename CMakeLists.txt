project(template_tree)

file(GLOB SOURCES "*.cpp")

add_executable(template_tree ${SOURCES})

set(CMAKE_CXX_FLAGS "-Wall")
OPTION(WITH_DEBUG_MODE "Build with debug mode" ON)
