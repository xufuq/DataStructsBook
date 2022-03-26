cmake_minimum_required(VERSION 3.2)
PROJECT(test)
INCLUDE_DIRECTORIES(
    include
)

set(SRC_LIST src/main.cpp include/dictionary.h include/sortedArrayList.h)
add_executable(arrayList ${SRC_LIST})
# TARGET_LINK_LIBRARIES(${PROJECT_NAME}  arrayList)


