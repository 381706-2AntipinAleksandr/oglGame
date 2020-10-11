cmake_minimum_required(VERSION 3.0)

project(Snake)

set(CMAKE_CXX_STANDARD 17)

#file(STRINGS src/ headers "*.h*")
#file(STRINGS src/ sources "*.cpp")

add_executable(${PROJECT_NAME} 
    src/main.cpp
    src/Render/ShaderRender.h
    src/Render/ShaderRender.cpp
    src/Resource/ResourceManager.h
    src/Resource/ResourceManager.cpp)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

add_subdirectory(external/glfw)
target_link_libraries(${PROJECT_NAME} glfw)

add_subdirectory(external/glad)
target_link_libraries(${PROJECT_NAME} glad)

set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIR ${CMAKE_BINARY_DIR}/bin/)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory
                   ${CMAKE_SOURCE_DIR}/resource $<TARGET_FILE_DIR:${PROJECT_NAME}>/resource)