CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT(lsd_1.6)
SET(CMAKE_CXX_STANDARD 11)
SET(CMAKE_CXX_FLAGS "-fPIC")
SET(CMAKE_BUILD_TYPE "Debug")

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(include)

#SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

add_library(Lsd_1.6_shared src/lsd.cpp include/lsd.h)

#add_executable(lsd_example ${PROJECT_SOURCE_DIR}/src_bin/lsd_call_example.cpp)
#add_executable(lsd ${PROJECT_SOURCE_DIR}/src_bin/lsd_cmd.cpp)
add_executable(lsd_duplicate ${PROJECT_SOURCE_DIR}/src_bin/lsd_cmd.cpp)
add_executable(lsd_test ${PROJECT_SOURCE_DIR}/src_bin/lsd_duplicate.cpp)

#target_link_libraries(lsd_example Lsd_1.6_shared ${OpenCV_LIBS} m)
#target_link_libraries(lsd Lsd_1.6_shared ${OpenCV_LIBS} m)
target_link_libraries(lsd_duplicate Lsd_1.6_shared ${OpenCV_LIBS} m)