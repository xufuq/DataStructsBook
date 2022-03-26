cmake_minimum_required(VERSION 3.2)
PROJECT(main)
INCLUDE_DIRECTORIES(
    include
)


set(SRC_LIST src/main.cpp include/linkedMatrix.h include/printError.h)
add_executable(main ${SRC_LIST})
# TARGET_LINK_LIBRARIES(${PROJECT_NAME}  arrayList)


