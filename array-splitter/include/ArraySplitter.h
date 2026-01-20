#ifndef ARRAY_SPLITTER_H
#define ARRAY_SPLITTER_H

#include <vector>
#include <stdexcept>
#include <string>
#include <type_traits>

// 命名空间隔离，避免命名冲突
namespace array_utils {

// 自定义异常：非法输入异常
class InvalidInputException : public std::invalid_argument {
public:
    explicit InvalidInputException(const std::string& message) 
        : std::invalid_argument(message) {}
};

// 自定义异常：无法分割异常
class SplitImpossibleException : public std::runtime_error {
public:
    explicit SplitImpossibleException(const std::string& message) 
        : std::runtime_error(message) {}
};

// 数组分割工具类（泛型模板，支持多种数值类型）
template <typename T>
class ArraySplitter {
public:
    // 核心功能1：判断数组是否能分割为k个和相等的非空部分
    static bool canSplitIntoKParts(const std::vector<T>& arr, int k);

    // 核心功能2：若能分割，返回分割后的k个子数组；否则抛出异常
    static std::vector<std::vector<T>> splitIntoKParts(const std::vector<T>& arr, int k);

    // 工具方法：计算数组总和（处理整数溢出）
    static long long calculateTotalSum(const std::vector<T>& arr);

private:
    // 内部辅助：校验输入合法性
    static void validateInput(const std::vector<T>& arr, int k);
};

} // namespace array_utils

#endif // ARRAY_SPLITTER_H