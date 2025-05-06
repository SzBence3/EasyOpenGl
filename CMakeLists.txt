# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.15)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("EasyOpengl")

# add include directories

# Include sub-projects.
add_subdirectory ("libs/glfw-3.4")
add_subdirectory("libs/glew-2.1.0/build/cmake")
#add_subdirectory("libs/glm-1.0.1")

add_subdirectory ("EasyOpengl")


target_include_directories(EasyOpengl PRIVATE 
  "libs"
  "libs/glm-1.0.1")
target_link_libraries(EasyOpengl glfw glew_s)

file(COPY ${CMAKE_SOURCE_DIR}/shaders
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/EasyOpengl)
file(COPY ${CMAKE_SOURCE_DIR}/res
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/EasyOpengl)

#-opengl32