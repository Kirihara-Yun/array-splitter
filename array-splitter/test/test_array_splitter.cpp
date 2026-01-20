#include <gtest/gtest.h>
#include "../include/ArraySplitter.h"

using namespace array_utils;

// 基础功能测试
TEST(ArraySplitterTest, BasicSplitTest) {
    // 测试1：正常3等分
    std::vector<int> arr1 = {1, 2, 3, 0, 3};
    EXPECT_TRUE(ArraySplitter<int>::canSplitIntoKParts(arr1, 3));
    
    // 测试2：全0数组3等分
    std::vector<int> arr2 = {0, 0, 0, 0};
    EXPECT_TRUE(ArraySplitter<int>::canSplitIntoKParts(arr2, 3));
    
    // 测试3：无法等分（总和不能被k整除）
    std::vector<int> arr3 = {1, 2, 3, 4, 5, 6};
    EXPECT_FALSE(ArraySplitter<int>::canSplitIntoKParts(arr3, 3));
    
    // 测试4：数组长度不足k
    std::vector<int> arr4 = {1, -1, 1, -1};
    EXPECT_FALSE(ArraySplitter<int>::canSplitIntoKParts(arr4, 5));
}

// 大数溢出测试
TEST(ArraySplitterTest, OverflowTest) {
    // 测试大数累加（1e9 * 3）
    std::vector<long long> arr = {1000000000LL, 1000000000LL, 1000000000LL};
    EXPECT_TRUE(ArraySplitter<long long>::canSplitIntoKParts(arr, 3));
    
    // 预期溢出异常
    std::vector<int> overflowArr = {INT_MAX, INT_MAX, INT_MAX};
    EXPECT_THROW(ArraySplitter<int>::calculateTotalSum(overflowArr), std::overflow_error);
}

// 分割结果测试
TEST(ArraySplitterTest, SplitResultTest) {
    std::vector<int> arr = {1, 2, 3, 0, 3};
    auto result = ArraySplitter<int>::splitIntoKParts(arr, 3);
    
    // 验证分割后的子数组数量
    EXPECT_EQ(result.size(), 3);
    // 验证每个子数组的和（目标和为 (1+2+3+0+3)/3 = 3）
    EXPECT_EQ(result[0][0] + result[0][1], 3); // [1,2]
    EXPECT_EQ(result[1][0], 3);               // [3]
    EXPECT_EQ(result[2][0] + result[2][1], 3); // [0,3]
}

// 异常处理测试
TEST(ArraySplitterTest, ExceptionTest) {
    std::vector<int> arr = {1, 2, 3};
    // 测试k=0的非法输入
    EXPECT_THROW(ArraySplitter<int>::splitIntoKParts(arr, 0), InvalidInputException);
    // 测试无法分割的场景
    std::vector<int> arr2 = {1, 2, 4};
    EXPECT_THROW(ArraySplitter<int>::splitIntoKParts(arr2, 3), SplitImpossibleException);
}

// 浮点类型测试
TEST(ArraySplitterTest, FloatTypeTest) {
    std::vector<double> arr = {1.5, 2.5, 2.0, 2.0};
    EXPECT_TRUE(ArraySplitter<double>::canSplitIntoKParts(arr, 2)); // 总和8，目标和4
    auto result = ArraySplitter<double>::splitIntoKParts(arr, 2);
    EXPECT_EQ(result[0][0] + result[0][1], 4.0); // [1.5,2.5]
    EXPECT_EQ(result[1][0] + result[1][1], 4.0); // [2.0,2.0]
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}