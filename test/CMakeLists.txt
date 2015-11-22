add_definitions(-std=c++11 -std=gnu99)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/../libcppjieba
    ${CMAKE_CURRENT_SOURCE_DIR}/../Chinese2Pinyin
)

add_executable(test_c2p
    test_c2p.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../Chinese2Pinyin/sds.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../Chinese2Pinyin/zmalloc.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../Chinese2Pinyin/functions.c
)
