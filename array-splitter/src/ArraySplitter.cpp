#include "ArraySplitter.h"
#include <iostream>

namespace array_utils {

// 输入合法性校验
template <typename T>
void ArraySplitter<T>::validateInput(const std::vector<T>& arr, int k) {
    if (k <= 0) {
        throw InvalidInputException("k must be a positive integer (k > 0)");
    }
    if (arr.size() < static_cast<size_t>(k)) {
        throw InvalidInputException(
            "Array length (" + std::to_string(arr.size()) + 
            ") is less than k (" + std::to_string(k) + "), cannot split into non-empty parts"
        );
    }
}

// 计算数组总和（针对整数类型做溢出防护，浮点类型直接累加）
template <typename T>
long long ArraySplitter<T>::calculateTotalSum(const std::vector<T>& arr) {
    long long totalSum = 0;
    // 对整数类型做溢出检查，浮点类型直接累加
    if constexpr (std::is_integral_v<T>) {
        for (const T& num : arr) {
            // 简单溢出预判（避免累加后溢出）
            if ((num > 0 && totalSum > LLONG_MAX - num) || (num < 0 && totalSum < LLONG_MIN - num)) {
                throw std::overflow_error("Integer overflow occurred when calculating total sum");
            }
            totalSum += num;
        }
    } else {
        for (const T& num : arr) {
            totalSum += static_cast<long long>(num);
        }
    }
    return totalSum;
}

// 判断是否能分割为k个和相等的非空部分
template <typename T>
bool ArraySplitter<T>::canSplitIntoKParts(const std::vector<T>& arr, int k) {
    try {
        validateInput(arr, k);
    } catch (const InvalidInputException& e) {
        return false;
    }

    long long totalSum = calculateTotalSum(arr);
    // 总和无法被k整除，直接返回false
    if (totalSum % k != 0) {
        return false;
    }

    long long target = totalSum / k;
    long long currentSum = 0;
    int count = 0;

    // 遍历累加，提前终止优化
    for (const T& num : arr) {
        currentSum += num;
        if (currentSum == target) {
            currentSum = 0;
            count++;
            if (count == k) {
                break;
            }
        }
    }

    return count >= k;
}

// 分割数组为k个和相等的非空部分（成功返回结果，失败抛异常）
template <typename T>
std::vector<std::vector<T>> ArraySplitter<T>::splitIntoKParts(const std::vector<T>& arr, int k) {
    validateInput(arr, k);

    long long totalSum = calculateTotalSum(arr);
    if (totalSum % k != 0) {
        throw SplitImpossibleException(
            "Total sum (" + std::to_string(totalSum) + 
            ") cannot be divided evenly by k (" + std::to_string(k) + ")"
        );
    }

    long long target = totalSum / k;
    long long currentSum = 0;
    int count = 0;
    std::vector<std::vector<T>> result;
    std::vector<T> currentPart;

    for (const T& num : arr) {
        currentSum += num;
        currentPart.push_back(num);

        // 凑出一个目标和，保存当前部分并重置
        if (currentSum == target) {
            result.push_back(currentPart);
            currentPart.clear();
            currentSum = 0;
            count++;

            // 提前终止：已凑够k个部分，忽略剩余元素
            if (count == k) {
                break;
            }
        }
    }

    // 验证是否凑够k个部分，避免特殊场景（如全0但未凑够）
    if (count < k) {
        throw SplitImpossibleException("Cannot split array into " + std::to_string(k) + " parts with equal sum");
    }

    return result;
}

// 显式实例化常用类型，避免编译链接问题
template class ArraySplitter<int>;
template class ArraySplitter<long long>;
template class ArraySplitter<float>;
template class ArraySplitter<double>;

} // namespace array_utils