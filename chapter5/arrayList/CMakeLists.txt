cmake_minimum_required(VERSION 3.2)
PROJECT(arrayList)
INCLUDE_DIRECTORIES(
    include
)


set(SRC_LIST src/main.cpp)
add_executable(arrayList ${SRC_LIST})
# TARGET_LINK_LIBRARIES(${PROJECT_NAME}  arrayList)


