cmake_minimum_required(VERSION 3.5)
project(graphic3d)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    figure/figure3d.h
    figure/plane.h
    figure/shape.h
    figure/sphere.h
        camera.cpp
    camera.h
        containers/figurelist.h
        intersecter/intersecter.cpp
        intersecter/intersecter_quadrangle.cpp
        intersecter/intersecter_triangle.cpp
        intersecter/intersecter_plane.cpp
        intersecter/intersecter_rectangle.cpp
        intersecter/intersecter_sphere.cpp
        intersecter/intersecter.h
        utils/line3d.cpp
        utils/line3d.h
        utils/numeric.h
        utils/numeric.cpp
    main.cpp
        screen/screen.cpp
        screen/screen.h
        utils/vec3d.cpp
        utils/vec3d.h
        utils/vec2d.h
        utils/polygon2d.h
        lights/light.h
        lights/light.cpp
        figure/traits.h
        screen/rgb.h
        screen/rgb.cpp
        containers/figurelist.cpp
        figure/shape.cpp beamtracer.h beamtracer.cpp reader/reader.h reader/reader.cpp containers/kdtree.h containers/kdtree.cpp settings.h color/color.h settings.cpp figure/flat.h figure/planelike.h utils/vec2d.cpp figure/box.cpp)

add_executable(graphic3d ${SOURCE_FILES})