cmake_minimum_required(VERSION 3.10)

# Set the project name and version
project(PlanningProject VERSION 1.0)

# Specify C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(OpenCV REQUIRED PATHS /usr/local/Cellar/opencv/4.11.0_1/lib)
find_package(yaml-cpp REQUIRED PATHS /usr/local/Cellar/yaml-cpp/0.8.0/lib/cmake/yaml-cpp)

# Manually find the yaml-cpp library
find_library(YAML_CPP_LIBRARY NAMES yaml-cpp PATHS /usr/local/Cellar/yaml-cpp/0.8.0/lib)

# where to look for header files
include_directories(${CMAKE_SOURCE_DIR}/src) 
include_directories("/usr/local/Cellar/opencv/4.11.0_1/include/opencv4")
include_directories(${YAML_CPP_INCLUDE_DIR})

# If yaml-cpp is not found automatically, use find_library to manually find it
if (NOT yaml-cpp_FOUND)
    find_library(YAML_CPP_LIBRARY yaml-cpp)
endif()

link_directories(${YAML_CPP_LIBRARY_DIR})

add_executable(runAStar
	${CMAKE_SOURCE_DIR}/src/runAStar.cpp
	${CMAKE_SOURCE_DIR}/src/Obstacle.cpp 
	${CMAKE_SOURCE_DIR}/src/Node.cpp
	${CMAKE_SOURCE_DIR}/src/AStar.cpp
	${CMAKE_SOURCE_DIR}/src/DrawMap.cpp
	${CMAKE_SOURCE_DIR}/src/DrawMapAStar.cpp)
add_executable(aStarRandom
	${CMAKE_SOURCE_DIR}/src/runAStarRandom.cpp
	${CMAKE_SOURCE_DIR}/src/Obstacle.cpp 
	${CMAKE_SOURCE_DIR}/src/Node.cpp
	${CMAKE_SOURCE_DIR}/src/StarNode.cpp
	${CMAKE_SOURCE_DIR}/src/AStarRandom.cpp
	${CMAKE_SOURCE_DIR}/src/DrawMap.cpp
	${CMAKE_SOURCE_DIR}/src/DrawMapAStarRandom.cpp)
add_executable(dStarLite
	${CMAKE_SOURCE_DIR}/src/runDStarLite.cpp
	${CMAKE_SOURCE_DIR}/src/Obstacle.cpp 
	${CMAKE_SOURCE_DIR}/src/Node.cpp
	${CMAKE_SOURCE_DIR}/src/StarNode.cpp
	${CMAKE_SOURCE_DIR}/src/DStarNode.cpp
	${CMAKE_SOURCE_DIR}/src/DStarLite.cpp
	${CMAKE_SOURCE_DIR}/src/DrawMap.cpp
	${CMAKE_SOURCE_DIR}/src/DrawMapDStarLite.cpp)
add_executable(runRRT
	${CMAKE_SOURCE_DIR}/src/runRRT.cpp
	${CMAKE_SOURCE_DIR}/src/Obstacle.cpp 
	${CMAKE_SOURCE_DIR}/src/Node.cpp
	${CMAKE_SOURCE_DIR}/src/DrawMap.cpp
	${CMAKE_SOURCE_DIR}/src/DrawMapRrt.cpp
	${CMAKE_SOURCE_DIR}/src/RRT.cpp)
add_executable(testPlanning
	${CMAKE_SOURCE_DIR}/src/testPlanning.cpp
	${CMAKE_SOURCE_DIR}/src/Obstacle.cpp 
	${CMAKE_SOURCE_DIR}/src/Node.cpp
	${CMAKE_SOURCE_DIR}/src/StarNode.cpp
	${CMAKE_SOURCE_DIR}/src/DStarNode.cpp
	${CMAKE_SOURCE_DIR}/src/DrawMap.cpp
	${CMAKE_SOURCE_DIR}/src/DrawMapAStar.cpp
	${CMAKE_SOURCE_DIR}/src/DrawMapRrt.cpp
	${CMAKE_SOURCE_DIR}/src/AStar.cpp
	${CMAKE_SOURCE_DIR}/src/RRT.cpp)
add_executable(testUpdateableMinHeap
	${CMAKE_SOURCE_DIR}/src/testUpdateableMinHeap.cpp
	${CMAKE_SOURCE_DIR}/src/UpdateableMinHeap.cpp)

# Link libraries
target_link_libraries(runAStar PRIVATE ${OpenCV_LIBS} ${YAML_CPP_LIBRARIES})
target_link_libraries(aStarRandom PRIVATE ${OpenCV_LIBS} ${YAML_CPP_LIBRARIES})
target_link_libraries(dStarLite PRIVATE ${OpenCV_LIBS} ${YAML_CPP_LIBRARIES})
target_link_libraries(runRRT PRIVATE ${OpenCV_LIBS} ${YAML_CPP_LIBRARIES})
target_link_libraries(testPlanning PRIVATE ${OpenCV_LIBS} ${YAML_CPP_LIBRARIES})


# Include directories for OpenCV and yaml-cpp
target_include_directories(runAStar PRIVATE ${OpenCV_INCLUDE_DIRS} ${YAML_CPP_INCLUDE_DIR})
target_include_directories(aStarRandom PRIVATE ${OpenCV_INCLUDE_DIRS} ${YAML_CPP_INCLUDE_DIR})
target_include_directories(dStarLite PRIVATE ${OpenCV_INCLUDE_DIRS} ${YAML_CPP_INCLUDE_DIR})
target_include_directories(runRRT PRIVATE ${OpenCV_INCLUDE_DIRS} ${YAML_CPP_INCLUDE_DIR})
target_include_directories(testPlanning PRIVATE ${OpenCV_INCLUDE_DIRS} ${YAML_CPP_INCLUDE_DIR})

