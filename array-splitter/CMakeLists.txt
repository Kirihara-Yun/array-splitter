cmake_minimum_required(VERSION 3.10)
project(array-splitter)

# 设置C++标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 编译选项：开启警告、优化
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -O2")

# 包含头文件目录
include_directories(include)

# 核心库（静态库）
add_library(array_splitter STATIC src/ArraySplitter.cpp)

# 单元测试（依赖Google Test）
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(test_array_splitter test/test_array_splitter.cpp)
target_link_libraries(test_array_splitter array_splitter ${GTEST_LIBRARIES} ${GTEST_MAIN_LIBRARIES} pthread)

# 安装目标（可选，便于系统级使用）
install(TARGETS array_splitter DESTINATION lib)
install(FILES include/ArraySplitter.h DESTINATION include)