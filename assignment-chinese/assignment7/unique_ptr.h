#pragma once

#include <cstddef>
#include <utility>

namespace cs106l {

/**
 * @brief 拥有一个对象、并在离开作用域时将其删除的智能指针。
 * @tparam T 要管理的对象类型。
 * @note 本类是 std::unique_ptr 的简化版本。
 */
template <typename T> class unique_ptr {
private:
  /* STUDENT TODO：unique_ptr 必须记录什么数据？ */

public:
  /**
   * @brief 根据给定指针构造新的 unique_ptr。
   * @param ptr 要管理的指针。
   * @note 应避免直接调用此构造函数，优先使用 make_unique()。
   */
  unique_ptr(T* ptr) {
    /* STUDENT TODO：实现构造函数。 */
    throw std::runtime_error("Not implemented: unique_ptr(T* ptr)");
  }

  /**
   * @brief 根据 nullptr 构造新的 unique_ptr。
   */
  unique_ptr(std::nullptr_t) {
    /* STUDENT TODO：实现 nullptr 构造函数。 */
    throw std::runtime_error("Not implemented: unique_ptr(std::nullptr_t)");
  }

  /**
   * @brief 构造空的 unique_ptr。
   * @note unique_ptr 默认指向 nullptr。
   */
  unique_ptr() : unique_ptr(nullptr) {}

  /**
   * @brief 解引用 unique_ptr，并返回对象引用。
   * @return 对象的引用。
   */
  T& operator*() {
    /* STUDENT TODO：实现解引用运算符。 */
    throw std::runtime_error("Not implemented: operator*()");
  }

  /**
   * @brief 解引用 unique_ptr，并返回对象的 const 引用。
   * @return 对象的 const 引用。
   */
  const T& operator*() const {
    /* STUDENT TODO：实现 const 版本的解引用运算符。 */
    throw std::runtime_error("Not implemented: operator*() const");
  }

  /**
   * @brief 返回指向 unique_ptr 所管理对象的指针。
   * @note 这样可以通过 -> 运算符访问被管理对象的成员。
   * @return 指向对象的指针。
   */
  T* operator->() {
    /* STUDENT TODO：实现箭头运算符。 */
    throw std::runtime_error("Not implemented: operator->()");
  }

  /**
   * @brief 返回指向 unique_ptr 所管理对象的 const 指针。
   * @note 这样可以通过 -> 运算符访问被管理对象的成员。
   * @return 指向对象的 const 指针。
   */
  const T* operator->() const {
    /* STUDENT TODO：实现箭头运算符。 */
    throw std::runtime_error("Not implemented: operator->() const");
  }

  /**
   * @brief 返回 unique_ptr 是否非空。
   * @note 这样可以在 if 语句中直接使用 unique_ptr。
   * @return 非空时为 true，否则为 false。
   */
  operator bool() const {
    /* STUDENT TODO：实现 bool 转换运算符。 */
    throw std::runtime_error("Not implemented: operator bool() const");
  }

  /** STUDENT TODO：在下方完成以下任务：
   * - 实现析构函数；
   * - 删除复制构造函数；
   * - 删除复制赋值运算符；
   * - 实现移动构造函数；
   * - 实现移动赋值运算符。
   */
};

/**
 * @brief 使用给定参数为某个类型创建新的 unique_ptr。
 * @example auto ptr = make_unique<int>(5);
 * @tparam T unique_ptr 所管理的类型。
 * @tparam Args 传给 T 构造函数的参数类型。
 * @param args 传给 T 构造函数的参数。
 */
template <typename T, typename... Args> 
unique_ptr<T> make_unique(Args&&... args) {
  return unique_ptr<T>(new T(std::forward<Args>(args)...));
}

}
