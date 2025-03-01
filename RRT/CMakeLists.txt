cmake_minimum_required(VERSION 3.10)

# Set the project name and version
project(RRTProject VERSION 1.0)

# Specify C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find OpenCV
find_package(OpenCV REQUIRED PATHS /usr/local/Cellar/opencv/4.11.0_1/lib)

# Check if OpenCV is found
if (NOT OpenCV_FOUND)
    message(FATAL_ERROR "OpenCV not found")
endif()

# Set the include and library paths manually
#set(YAML_CPP_INCLUDE_DIRS /usr/local/Cellar/yaml-cpp/0.8.0/include)
#set(YAML_CPP_LIBRARIES /usr/local/Cellar/yaml-cpp/0.8.0/lib/libyaml-cpp.dylib)

# Find yaml-cpp
##find_package(yaml-cpp REQUIRED PATHS /usr/local/Cellar/yaml-cpp/0.8.0/lib/cmake/yaml-cpp)

# Manually find the yaml-cpp library
find_library(YAML_CPP_LIBRARY NAMES yaml-cpp PATHS /usr/local/Cellar/yaml-cpp/0.8.0/lib)





# Add the src folder to the project
include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories("/usr/local/Cellar/opencv/4.11.0_1/include/opencv4")
# Link libraries and include directories
include_directories(${YAML_CPP_INCLUDE_DIRS})


# If yaml-cpp is not found automatically, use find_library to manually find it
if (NOT yaml-cpp_FOUND)
    find_library(YAML_CPP_LIBRARY yaml-cpp)
endif()


# Add executable
add_executable(runRRT ${CMAKE_SOURCE_DIR}/src/runRRT.cpp ${CMAKE_SOURCE_DIR}/src/RRT.cpp)

# Link libraries
target_link_libraries(runRRT PRIVATE ${OpenCV_LIBS} ${YAML_CPP_LIBRARY})
#target_link_libraries(runRRT PRIVATE ${OpenCV_LIBS} yaml-cpp)

# Include directories for OpenCV and yaml-cpp
target_include_directories(runRRT PRIVATE ${OpenCV_INCLUDE_DIRS} ${YAML_CPP_INCLUDE_DIRS})

