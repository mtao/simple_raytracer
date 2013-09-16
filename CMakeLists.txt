cmake_minimum_required(VERSION 2.6)
PROJECT(SimpleRaytracer)

SET(CMAKE_RUNTIME_OUTPUT_DIR ${PROJECT_BINARY_DIR}/bin)
SET(CMAKE_LIBRARY_OUTPUT_DIR ${PROJECT_BINARY_DIR}/lib)
SET(CMAKE_ARCHIVE_OUTPUT_DIR ${PROJECT_BINARY_DIR}/lib)

ADD_DEFINITIONS(-std=c++11)
ADD_DEFINITIONS(-Werror)
ADD_DEFINITIONS(-Wall)
#ADD_DEFINITIONS(-pg)
FIND_PACKAGE( OpenMP )
IF(OpenMP_FOUND)
SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
ADD_DEFINITIONS(-DUSING_OPENMP)
ENDIF(OpenMP_FOUND)

# Include dirs
INCLUDE_DIRECTORIES(/opt/boost_1_44_0/include ${CMAKE_CURRENT_SOURCE_DIR}/include /usr/local/include/eigen3)
# Autogen'd moc code appears in the BINARY_DIR I believe
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR})

SET(CMAKE_INCLUDE_CURRENT_DIR_ON)
SET(CMAKE_AUTOMOC ON)
FIND_PACKAGE(Qt5Core)


# Source files
SET(SimpleRaytracer_SOURCES
    src/scene.cpp
    src/sphere.cpp
    src/film.cpp
    src/camera.cpp
    src/main.cpp
    src/phong_light.cpp
    )
# Include files
SET(SimpleRaytracer_HEADERS
    include/intersection.hpp
    include/ray.hpp
    include/scene.hpp
    include/renderable.hpp
    include/types.hpp
    include/sphere.hpp
    include/film.hpp
    include/camera.hpp
    include/phong_light.hpp
    include/phong_material.hpp
    include/color.hpp
    )

# Executable to build
ADD_EXECUTABLE(SimpleRaytracer
    ${SimpleRaytracer_SOURCES}
    ${SimpleRaytracer_HEADERS})

QT5_USE_MODULES(SimpleRaytracer Gui)
