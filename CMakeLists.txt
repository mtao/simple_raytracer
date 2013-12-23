cmake_minimum_required(VERSION 2.6)
PROJECT(SimpleRaytracer)

SET(CMAKE_RUNTIME_OUTPUT_DIR ${PROJECT_BINARY_DIR}/bin)
SET(CMAKE_LIBRARY_OUTPUT_DIR ${PROJECT_BINARY_DIR}/lib)
SET(CMAKE_ARCHIVE_OUTPUT_DIR ${PROJECT_BINARY_DIR}/lib)

ADD_DEFINITIONS(-std=c++11)
#ADD_DEFINITIONS(-Werror)
ADD_DEFINITIONS(-Wall)
#ADD_DEFINITIONS(-pg)
FIND_PACKAGE( OpenMP )
IF(OpenMP_FOUND)
SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
ADD_DEFINITIONS(-DUSING_OPENMP)
ENDIF(OpenMP_FOUND)

FIND_PACKAGE( GLEW )
IF(GLEW_FOUND)
    INCLUDE_DIRECTORIES(${GLEW_INCLUDE_DIRS})
ENDIF(GLEW_FOUND)


# Include dirs
INCLUDE_DIRECTORIES(/opt/boost_1_44_0/include ${CMAKE_CURRENT_SOURCE_DIR}/include /usr/local/include/eigen3 /usr/local/include/eigen3/unsupported)
# Autogen'd moc code appears in the BINARY_DIR I believe
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR})

SET(CMAKE_INCLUDE_CURRENT_DIR_ON)
SET(CMAKE_AUTOMOC ON)
FIND_PACKAGE(Qt5Core)


# Source files
SET(SimpleRaytracerCore_SOURCES
    src/scene.cpp
    src/sphere.cpp
    src/film.cpp
    src/camera.cpp
    src/phong_light.cpp
    src/scene_graph_optimizer.cpp
    src/point.cpp
    )
# Include files
SET(SimpleRaytracerCore_HEADERS
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
    include/scene_graph_optimizer.hpp
    )


SET(SimpleRaytracerGUI_SOURCES
    src/main_gl.cpp
    src/mainwindow.cpp
    src/glwidget.cpp
    )

SET(SimpleRaytracerGUI_HEADERS
    include/mainwindow.hpp
    include/glwidget.hpp
    )


# Executable to build
ADD_EXECUTABLE(simple_raytracer
    src/main_cl.cpp
    ${SimpleRaytracerCore_SOURCES}
    ${SimpleRaytracerCore_HEADERS})
ADD_EXECUTABLE(simple_raytracer-qt5
    ${SimpleRaytracerCore_SOURCES}
    ${SimpleRaytracerCore_HEADERS}
    ${SimpleRaytracerGUI_SOURCES}
    ${SimpleRaytracerGUI_HEADERS}
    )
TARGET_LINK_LIBRARIES(simple_raytracer-qt5 GL ${GLEW_LIBRARIES})
SET_TARGET_PROPERTIES(simple_raytracer-qt5 PROPERTIES COMPILE_DEFINITIONS "USING_OPENGL")

QT5_USE_MODULES(simple_raytracer Gui)
QT5_USE_MODULES(simple_raytracer-qt5 Gui OpenGL Widgets)
