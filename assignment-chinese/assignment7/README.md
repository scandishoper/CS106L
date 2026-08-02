<p align="center">
  <img src="docs/art.png" alt="作业插图" />
</p>

# 作业 7：独占指针

截止时间：5 月 31 日（星期日）23:59

## 概述

本作业需要自行实现一个简化版 `unique_ptr`，从而练习本周课程介绍的 RAII 与智能指针。你还会综合使用本课程的其他知识：模板、运算符重载和移动语义。

你会修改三个文件：

- `unique_ptr.h`：包含 `unique_ptr` 实现的全部代码。
- `main.cpp`：包含使用 `unique_ptr` 的代码；你需要在这里实现一个函数。
- `short_answer.txt`：包含需要在作业过程中回答的简答题。

## 运行代码

打开终端（VSCode 中可按 <kbd>Ctrl+`</kbd>，或选择 **Terminal > New Terminal**），确认当前位于 `assignment7/` 目录，然后编译：

```sh
g++ -std=c++20 main.cpp -o main
```

如果编译没有报错，请运行 `./main`。建议在完成下述步骤时经常编译并运行自动评分器。

> [!NOTE]
>
> ### Windows 用户说明
>
> Windows 上可能需要使用以下命令编译：
>
> ```sh
> g++ -static-libstdc++ -std=c++20 main.cpp -o main
> ```
>
> 生成的文件也可能名为 `main.exe`，此时请运行 `./main.exe`。

## 第 1 部分：实现 `unique_ptr`

首先实现周四课程介绍的智能指针之一：`unique_ptr`。这里的版本比标准库 [`std::unique_ptr`](https://en.cppreference.com/w/cpp/memory/unique_ptr) 更简单。`unique_ptr` 表示一块动态分配的内存，该内存只由一个（即“独占”）变量拥有。变量离开作用域时，会自动调用 `delete` 释放自己拥有的内存。这种行为称为 RAII（资源获取即初始化）。**本作业可以假设 `unique_ptr` 始终指向一个 `T` 类型的单独元素；无需调用 `delete[]`，也无需处理动态数组指针。**

> [!IMPORTANT]
>
> ##### `short_answer.txt`
>
> **问题 1：**相比手动调用 `new` 和 `delete`，使用 RAII 管理内存有哪些好处？请列出一到两点。

> [!NOTE]
> 当前 `unique_ptr` 不支持数组指针，但可以通过*模板特化*添加支持。标准库 `std::unique_ptr` 就使用模板特化为数组提供不同实现，例如：
>
> ```cpp
> template <typename T>
> class unique_ptr<T[]>;
> ```
>
> 这样会得到两个版本：一个处理单独元素，另一个处理元素数组。两者支持的操作也不同，例如数组版本提供下标运算符 `operator[]`，而单元素版本没有。

### 实现 `unique_ptr` 的基础功能

先阅读 `unique_ptr.h` 中提供的代码。仓库已经给出 `unique_ptr` 的基础接口，你需要实现它。`unique_ptr` 应像普通指针一样工作，支持解引用（`operator*`）和成员访问（`operator->`）等操作。为保证类满足 `const` 正确性，其中一些方法同时提供 `const` 与非 `const` 版本。

请实现以下内容。每项通常只需在 `unique_ptr.h` 中添加或修改 1～2 行：

- `unique_ptr` 的 `private` 部分
- `unique_ptr(T* ptr)` 构造函数
- `unique_ptr(std::nullptr_t)` 空指针构造函数
- `T& operator*()`
- `const T& operator*() const`
- `T* operator->()`
- `const T* operator->() const`
- `operator bool() const`

### 实现 RAII

完成以上内容后，`unique_ptr` 的行为与原始指针相似，但它仍不会在变量离开作用域时自动释放内存，而且它还不具备“独占”性：可以随意复制多个指向同一内存的对象。假设 `unique_ptr` 离开作用域时会正确清理数据，考虑以下代码：

```cpp
int main()
{
  unique_ptr<int> ptr1 = make_unique<int>(5);

  // ptr1 指向堆上动态分配的整数 5
  {
    unique_ptr<int> ptr2 = ptr1; // 浅复制
  } // ptr2 的数据在此释放

  std::cout << *ptr1 << std::endl;
  return 0;
}
```

由于 `ptr1` 与 `ptr2` 指向同一块内存，`ptr2` 离开作用域时也会释放 `ptr1` 的数据，之后访问 `*ptr1` 会产生未定义行为。

另一方面，`unique_ptr` 应当支持**移动**。移动语义允许我们转移对象资源的所有权，而不进行昂贵复制。移动独占指针不会破坏其唯一性：任意时刻底层内存仍然只有一个拥有者，只是拥有内存的变量发生了变化。

为实现自动释放、禁止复制并支持移动，需要实现以下特殊成员函数（SMF）：

- `~unique_ptr()`：释放指针所指内存。
- `unique_ptr(const unique_ptr& other)`：复制构造函数，应将其删除。
- `unique_ptr& operator=(const unique_ptr& other)`：复制赋值运算符，应将其删除。
- `unique_ptr(unique_ptr&& other)`：移动构造函数。
- `unique_ptr& operator=(unique_ptr&& other)`：移动赋值运算符。

完成后，应能通过自动评分器中**第 1 部分**的全部测试。

> [!IMPORTANT]
>
> ##### `short_answer.txt`
>
> **问题 2：**实现 `unique_ptr` 的移动语义时，例如在 `unique_ptr(unique_ptr&& other)` 中，函数结束前必须把 `other` 的底层指针设为 `nullptr`。请解释如果不这样做会产生什么问题。

## 第 2 部分：使用 `unique_ptr`

实现 `unique_ptr` 后，开始实际使用它。`main.cpp` 中提供了一个完整的单链表节点 `ListNode`，它使用 `unique_ptr` 保证所有节点都会被正确释放。例如：

```cpp
int main()
{
  auto head = cs106l::make_unique<ListNode<int>>(1);
  head->next = cs106l::make_unique<ListNode<int>>(2);
  head->next->next = cs106l::make_unique<ListNode<int>>(3);

  // head 的内存结构：
  //
  // head -> (1) -> (2) -> (3) -> nullptr
} // 在这里析构 head

// 输出：
// Constructing node with value '1'
// Constructing node with value '2'
// Constructing node with value '3'
// Destructing node with value '1'
// Destructing node with value '2'
// Destructing node with value '3'
```

注意，代码没有调用任何 `delete`。`unique_ptr` 的 RAII 行为保证链表中的内存会递归释放：`head` 离开作用域后析构节点 `(1)`，它继续析构 `(2)`，再析构 `(3)`。

> [!IMPORTANT]
>
> ##### `short_answer.txt`
>
> **问题 3：**通过 RAII 递归释放对短链表很有效，但长链表可能出现问题。为什么？提示：递归函数调用栈的深度有什么限制？

**你的任务是实现 `create_list`，把 `std::vector<T>` 转换为 `unique_ptr<ListNode<T>>`。**向量中的元素顺序在链表中必须保持不变；空向量应返回 `nullptr`。一种做法是倒序构造链表，从尾节点逐步建立到头节点。**必须使用 `cs106l` 命名空间下的 `cs106l::unique_ptr`，不能使用 `std::unique_ptr`。**建议按照以下算法实现：

1. 初始化 `cs106l::unique_ptr<ListNode<T>> head = nullptr`。
2. **倒序**遍历 `std::vector`，对每个元素：
   - 2a. 创建新的 `cs106l::unique_ptr<ListNode<T>> node`，其值为当前向量元素。
   - 2b. 把 `node->next` 设为 `head`。
   - 2c. 把 `head` 设为 `node`。
3. 返回 `head`。

> [!IMPORTANT]
>
> ##### `short_answer.txt`
>
> **问题 4：**实现 2b、2c 时，如果直接把 `head` 赋给 `node->next`，编译器会报错，指出不存在复制赋值运算符。这是正确的，因为 `unique_ptr` 不能复制。
>
> 我们必须强制编译器执行**移动赋值**，例如写成 `node->next = std::move(head)`。此处 `std::move` 做了什么？为什么这里使用移动语义是安全的？

> [!NOTE]
> 倒序遍历向量时，谨慎使用 `size_t` 作为下标。`size_t` 只能表示非负整数，下标减到零以下时会发生无符号整数回绕，导致循环边界出现意外行为。可以改用 `int`。

实现 `create_list` 后，即可创建并打印链表。若想进行额外练习，可以查看 `map_list()` 和 `linked_list_example()`；它们会调用 `create_list`，并逐行打印元素。此时应能通过自动评分器中**第 2 部分**的全部测试。

## 🚀 提交说明

通过全部测试后即可提交：

1. 填写[反馈表](https://forms.gle/uHr3J8Vm3gECkZpm9)。
2. 在 [Paperless](https://paperless.stanford.edu) 上提交作业。

需要提交：

- `unique_ptr.h`
- `main.cpp`
- `short_answer.txt`

截止时间前可以重复提交任意次数。
