/** 包含内存诊断工具，用于跟踪内存分配并报告内存泄漏。 */

#pragma once

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <new>
#include <unordered_map>

namespace MemoryDiagnostics {
namespace detail {

/**
 * 为了初始化下方 MemoryTracker 类中的 unordered_map，必须进行动态内存分配。
 * 但 unordered_map 的默认分配器会调用 operator new 和 delete，从而造成无限递归。
 * 为避免这一问题，这里定义使用 std::malloc 和 std::free 的自定义分配器，
 * 并让 MemoryTracker 中的 unordered_map 使用该分配器。
 *
 * 更多信息见 https://en.cppreference.com/w/cpp/named_req/Allocator 。
 */
template <class T> struct Mallocator {
  using value_type = T;

  Mallocator() = default;

  template <class U> constexpr Mallocator(const Mallocator<U>&) noexcept {}

  [[nodiscard]] T* allocate(std::size_t n) {
    if (n > std::numeric_limits<std::size_t>::max() / sizeof(T))
      throw std::bad_array_new_length();

    if (auto p = static_cast<T*>(std::malloc(n * sizeof(T)))) {
      return p;
    }

    throw std::bad_alloc();
  }

  void deallocate(T* p, std::size_t n) noexcept { std::free(p); }
};

template <class T, class U> bool operator==(const Mallocator<T>&, const Mallocator<U>&) {
  return true;
}

template <class T, class U> bool operator!=(const Mallocator<T>&, const Mallocator<U>&) {
  return false;
}

class MemoryTracker {
  using AllocationsMap = std::unordered_map<void*, size_t, std::hash<void*>, std::equal_to<void*>,
                                            Mallocator<std::pair<void* const, size_t>>>;
  size_t bytes_outstanding = 0;
  AllocationsMap allocations;

public:
  void* allocate(size_t size) {
    if (size == 0)
      ++size; // 避免 std::malloc(0) 在成功时仍返回 nullptr。

    void* ptr = std::malloc(size);
    if (ptr == nullptr)
      throw std::bad_alloc{}; // [new.delete.single]/3 的要求。

    bytes_outstanding += size;
    allocations[ptr] = size;
    return ptr;
  }

  void deallocate(void* ptr) {
    std::free(ptr);
    auto it = allocations.find(ptr);
    if (it != allocations.end()) {
      bytes_outstanding -= it->second;
      allocations.erase(it);
    }
  }

  size_t get_bytes_outstanding() const { return bytes_outstanding; }
};

MemoryTracker& get_tracker() {
  static MemoryTracker tracker;
  return tracker;
}

} // namespace detail

/**
 * MemoryGuard 确保构造时与析构时的动态分配字节数一致。
 * 如果二者不一致，它会把错误消息打印到 stderr，
 * 并使用预定义退出码终止程序。
 */
class MemoryGuard {
public:
  MemoryGuard(const char* message)
      : message(message), initial_bytes_outstanding(detail::get_tracker().get_bytes_outstanding()) {
  }

  ~MemoryGuard() {
    if (initial_bytes_outstanding != detail::get_tracker().get_bytes_outstanding()) {
      if (message)
        std::cerr << message << std::endl;
      std::exit(exit_code);
    }
  }

  static int get_exit_code() { return exit_code; }

private:
  const char* message = nullptr;
  size_t initial_bytes_outstanding;
  static constexpr const int exit_code = 106;
};

} // namespace MemoryDiagnostics

void* operator new(std::size_t sz) { return MemoryDiagnostics::detail::get_tracker().allocate(sz); }

void* operator new[](std::size_t sz) {
  return MemoryDiagnostics::detail::get_tracker().allocate(sz);
}

void operator delete(void* ptr) noexcept {
  MemoryDiagnostics::detail::get_tracker().deallocate(ptr);
}

void operator delete(void* ptr, std::size_t size) noexcept {
  MemoryDiagnostics::detail::get_tracker().deallocate(ptr);
}

void operator delete[](void* ptr) noexcept {
  MemoryDiagnostics::detail::get_tracker().deallocate(ptr);
}

void operator delete[](void* ptr, std::size_t size) noexcept {
  MemoryDiagnostics::detail::get_tracker().deallocate(ptr);
}
