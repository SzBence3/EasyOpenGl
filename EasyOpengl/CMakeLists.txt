# CMakeList.txt : CMake project for EasyOpengl, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (EasyOpengl "EasyOpengl.cpp" 
 "Window.cpp" "Monitor.h" "Monitor.cpp" "libinit.h" "libinit.cpp" "Event.h" "Event.cpp" "EventCallback.cpp")

 target_include_directories(EasyOpengl 
 PRIVATE 
	${CMAKE_SOURCE_DIR}/libs/glfw-3.4/include
	${CMAKE_SOURCE_DIR}/libs/glew-2.1.0/include
	${CMAKE_SOURCE_DIR}/libs/glm-master
)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET EasyOpengl PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
