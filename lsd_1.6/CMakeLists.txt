CMAKE_MINIMUM_REQUIRED(VERSION 2.8)                                              #cmake需要的最低版本

PROJECT(lsd_1.6)                                                                 #项目名称lsd_1.6

SET(CMAKE_C_STANDARD 11)                                                         #编译器gcc标准

SET(CMAKE_C_FLAGS "-fPIC")                                                       #-FPIC的作用在于告诉编译器产生与位置无关的代码(Position-Independent code)
                                                                                 #则产生的代码中,没有绝对地址,全是相对地址,故而代码可以被加载器加载到内存的任意位置,都可以正确执行

SET(CMAKE_BUILD_TYPE "Debug")                                                    #通过debug模式构建项目


find_package(OpenCV REQUIRED)                                                   #找到OpenCV的库
include_directories(${OpenCV_INCLUDE_DIRS})                                     #将包含OpenCV库头文件的文件夹包含进去,以此可以调用OpenCV
include_directories(include)                                                     #包含include文件夹,以此调用include文件夹里的头文件

#SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)                           #设置可执行文件生成的目录路径

SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)                               #设置库文件生成的目录路径

add_library(Lsd_1.6_shared SHARED src/lsd.c include/lsd.h)                       #将项目的源文件及头文件编译生成共享库

add_executable(lsd_example ${PROJECT_SOURCE_DIR}/src_bin/lsd_call_example.c)     #生成可执行程序
add_executable(lsd ${PROJECT_SOURCE_DIR}/src_bin/lsd_cmd.c)

target_link_libraries(lsd_example Lsd_1.6_shared m)# ${OpenCV_LIBS} m)          #将可执行程序和所需要的库进行链接
target_link_libraries(lsd Lsd_1.6_shared m)# ${OpenCV_LIBS} m)
