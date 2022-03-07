cmake_minimum_required(VERSION 3.21)
project(path_tracer)

set(CMAKE_CXX_STANDARD 20)
find_package (Eigen3 3.3 REQUIRED NO_MODULE)

find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

add_executable(path_tracer src/main.cpp src/scene/Scene.cpp src/scene/Scene.h src/geometry/Object.cpp src/geometry/Object.h src/scene/Bvh.cpp src/scene/Bvh.h src/geometry/Ray.cpp src/geometry/Ray.h src/constants.h src/scene/Camera.cpp src/scene/Camera.h src/material/Material.cpp src/material/Material.h src/material/BSDF.cpp src/material/BSDF.h src/PathIntegrator.cpp src/PathIntegrator.h src/types.h src/lights/PointLight.cpp src/lights/PointLight.h src/geometry/Sphere.cpp src/geometry/Sphere.h src/material/Diffuse.cpp src/material/Diffuse.h src/geometry/Plane.cpp src/geometry/Plane.h src/geometry/Triangle.cpp src/geometry/Triangle.h)
target_link_libraries (path_tracer Eigen3::Eigen)
target_link_libraries( path_tracer ${OpenCV_LIBS} )

