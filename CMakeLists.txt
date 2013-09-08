cmake_minimum_required(VERSION 2.6)
PROJECT(SimpleRaytracer)

SET(CMAKE_RUNTIME_OUTPUT_DIR ${PROJECT_BINARY_DIR}/bin)
SET(CMAKE_LIBRARY_OUTPUT_DIR ${PROJECT_BINARY_DIR}/lib)
SET(CMAKE_ARCHIVE_OUTPUT_DIR ${PROJECT_BINARY_DIR}/lib)

ADD_DEFINITIONS(-std=c++11)
ADD_DEFINITIONS(-Werror)
ADD_DEFINITIONS(-Wall)

# Include dirs
INCLUDE_DIRECTORIES(/opt/boost_1_44_0/include ${CMAKE_CURRENT_SOURCE_DIR}/include /usr/local/include/eigen3)
# Autogen'd moc code appears in the BINARY_DIR I believe
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR})


# Source files
SET(SimpleRaytracer_SOURCES
    src/scene.cpp
    src/sphere.cpp
    )
# Include files
SET(SimpleRaytracer_HEADERS
    include/intersection.hpp
    include/ray.hpp
    include/scene.hpp
    include/renderable.hpp
    include/types.hpp
    include/sphere.hpp
    )

# Executable to build
ADD_EXECUTABLE(SimpleRaytracer
    ${SimpleRaytracer_SOURCES}
    ${SimpleRaytracer_HEADERS})

