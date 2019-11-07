CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT(opencv_idz)
SET(CMAKE_CXX_STANDARD 11)
SET(CMAKE_CXX_FLAGS "-fPIC")
SET(CMAKE_BUILD_TYPE "Debug")

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(include)

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

add_library(opencv_idz_shared src/EDLines.cpp include/EDLines.h)

add_executable(Opencv_idz ${PROJECT_SOURCE_DIR}/src_bin/main.cpp)

target_link_libraries(Opencv_idz opencv_idz_shared ${OpenCV_LIBS})
