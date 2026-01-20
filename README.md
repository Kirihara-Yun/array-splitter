# array-splitter
高性能、通用化的数组等分工具库，支持任意k等分判断与实际分割，覆盖整数/浮点类型，具备完善的异常处理和性能优化。

## 功能特性
- ✅ 通用化：支持任意正整数k的数组等分判断
- ✅ 多类型：泛型模板支持int/long long/float/double等数值类型
- ✅ 高性能：O(n)时间复杂度、提前终止遍历、整数溢出防护
- ✅ 实用扩展：不仅判断是否可分割，还能返回实际分割后的子数组
- ✅ 健壮性：自定义异常、完善的输入校验、边界场景全覆盖
- ✅ 工程化：命名空间隔离、静态库编译、单元测试全覆盖

## 安装使用
### 环境依赖
- C++17及以上编译器（GCC/Clang/MSVC）
- CMake 3.10+（编译）
- Google Test（单元测试，可选）

### 编译步骤
```bash
# 克隆仓库
git clone https://github.com/Kirihara-Yun/array-splitter.git
cd array-splitter

# 编译构建
mkdir build && cd build
cmake ..
make

# 运行单元测试
./test_array_splitter
