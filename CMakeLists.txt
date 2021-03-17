cmake_minimum_required(VERSION 3.17)
project(cpp_examples_new)

set(CMAKE_CXX_STANDARD 20)

add_executable(cpp_examples_new main.cpp dat.h rocks.cpp rocks.h)


set (Boost_USE_STATIC_LIBS OFF)


#https://stackoverflow.com/questions/56511716/cmake-file-for-a-folly-project


find_package(folly REQUIRED)

find_package(Threads REQUIRED)
find_package(gflags REQUIRED)
find_package (Boost COMPONENTS  locale iostreams system filesystem REQUIRED)


find_path(ROCKSDB_ROOT_DIR
        NAMES include/rocksdb/db.h)

find_library(ROCKSDB_LIBRARIES
        NAMES rocksdb
        HINTS ${ROCKSDB_ROOT_DIR})

find_path(ROCKSDB_INCLUDE_DIR
        NAMES rocksdb/db.h
        HINTS ${ROCKSDB_ROOT_DIR}/include)

list(APPEND CMAKE_MODULE_PATH  ${CMAKE_CURRENT_LIST_DIR}/cmake)

include_directories (${Boost_INCLUDE_DIRS})
include_directories(${folly_INCLUDE_DIRS})
include_directories (${ROCKSDB_INCLUDE_DIR})


set(FOLLY_LIBRARIES Folly::folly)
TARGET_LINK_LIBRARIES( cpp_examples_new LINK_PUBLIC  ${Boost_LIBRARIES} ${FOLLY_LIBRARIES} ${ROCKSDB_LIBRARIES})