# 作业 6：Explore Courses

截止时间：5 月 22 日（星期五）23:59

## 概述

本作业用于练习对 `std::optional` 的理解，并继续使用作业 1 中的 `courses.csv`。你只需编写一个函数：尝试在 `CourseDatabase` 对象中查找某个 `Course` 并将其返回。你还会探索 `std::optional` 提供的单子操作。请先阅读代码并查看 `CourseDatabase` 类，理解其接口。

## 运行代码

打开终端（VSCode 中可按 <kbd>Ctrl+`</kbd>，或选择 **Terminal > New Terminal**），确认当前位于 `assignment6/` 目录，然后编译：

```sh
g++ -std=c++23 main.cpp -o main
```

如果编译没有报错，请运行 `./main`。建议在完成下述步骤时经常编译并运行自动评分器。

> [!NOTE]
>
> ### Windows 用户说明
>
> Windows 上可能需要使用以下命令编译：
>
> ```sh
> g++ -static-libstdc++ -std=c++23 main.cpp -o main
> ```
>
> 生成的文件也可能名为 `main.exe`，此时请运行 `./main.exe`。

## 第 0 部分：包含 `<optional>`

在 `main.cpp` 顶部包含 `<optional>`；本作业会使用 `std::optional`。

## 第 1 部分：编写 `find_course`

该函数接收字符串 `course_title`，并尝试在 `CourseDatabase` 对象的私有成员 `courses` 中查找对应 `course`。返回类型应该是什么？提示：传入的 `course_title` 可能有对应课程，也可能没有。

> [!NOTE]
> 需要修改 `find_course` 当前的返回类型 `FillMeIn`。

## 第 2 部分：修改 `main`

`main` 中通过以下代码调用 `find_course`：

```cpp
auto course = db.find_course(argv[1]);
```

接下来使用 [`std::optional` 的单子操作](https://en.cppreference.com/w/cpp/utility/optional)正确生成字符串 `output`。目标是在**不使用 `if` 等条件语句**的情况下复现以下行为：

```cpp
if (course.has_value()) {
    std::cout << "Found course: " << course->title << ","
              << course->number_of_units << "," << course->quarter << "\n";
} else {
    std::cout << "Course not found.\n";
}
```

如果找到课程，`main` 底部输出 `output` 时应产生：

```text
Found course: <title>,<number_of_units>,<quarter>
```

如果没有找到，则应产生：

```text
Course not found.
```

### 单子操作

共有三个单子操作：[`and_then`](https://en.cppreference.com/w/cpp/utility/optional/and_then)、[`transform`](https://en.cppreference.com/w/cpp/utility/optional/transform) 和 [`or_else`](https://en.cppreference.com/w/cpp/utility/optional/or_else)。请阅读课程幻灯片和[标准库文档](https://en.cppreference.com/w/cpp/utility/optional)中的说明。本题只需要其中两个。

代码结构应类似：

```cpp
std::string output = course
    ./* 第一个单子操作 */ (/* ... */)
    ./* 第二个单子操作 */ (/* ... */)
    .value();                                  // 也可用 `.value_or(...)`，见下文
```

可以先确定 `output` 的类型，再从结果反向推导。请仔细分析以下三个操作各自的作用。

> [!NOTE]
> 假设 `T` 和 `U` 是任意类型：
>
> ```cpp
> /**
>  * 简而言之：有值时调用函数产生新的 optional，否则返回空值。
>  *
>  * 传给 and_then 的函数接收非 optional 的 T，并返回 std::optional<U>。
>  * optional 有值时，对该值调用函数并返回结果；没有值（即 std::nullopt）时，
>  * 返回 std::nullopt。
>  */
> template <typename U>
> std::optional<U> std::optional<T>::and_then(
>     std::function<std::optional<U>(T)> func);
>
> /**
>  * 简而言之：有值时转换该值并把结果包装进 optional，否则返回空值。
>  *
>  * 传给 transform 的函数接收非 optional 的 T，并返回非 optional 的 U。
>  * optional 有值时，对该值调用函数，并返回包装为 std::optional<U> 的结果；
>  * 没有值时返回 std::nullopt。
>  */
> template <typename U>
> std::optional<U> std::optional<T>::transform(std::function<U(T)> func);
>
> /**
>  * 简而言之：有值时返回自身，否则调用函数产生新的 optional。
>  *
>  * 它与 and_then 相反。传入的函数不接收参数，并返回 std::optional<U>。
>  * optional 有值时，or_else 返回自身；没有值时调用函数并返回其结果。
>  */
> template <typename U>
> std::optional<U> std::optional<T>::or_else(
>     std::function<std::optional<U>()> func);
> ```
>
> 对一个 `std::optional<T> opt`，可以这样调用：
>
> ```cpp
> opt
>   .and_then([](T value) -> std::optional<U> { return /* ... */; })
>   .transform([](T value) -> U { return /* ... */; })
>   .or_else([]() -> std::optional<U> { return /* ... */; });
> ```
>
> <sup>lambda 中的 `->` 用于显式写出函数返回类型。</sup>
>
> 由于每个方法都返回 `std::optional`，它们可以链式调用。如果确定链式操作结束时一定有值，可以调用 [`.value()`](https://en.cppreference.com/w/cpp/utility/optional/value) 取得该值；否则可调用 [`.value_or(fallback)`](https://en.cppreference.com/w/cpp/utility/optional/value_or)，在空值时返回备用值 `fallback`。

## 🚀 提交说明

通过全部测试后即可提交：

1. 填写[反馈表](https://forms.gle/aGuFqLyhB18mNoPKA)。
2. 在 [Paperless](https://paperless.stanford.edu) 上提交作业。

需要提交：

- `main.cpp`

截止时间前可以重复提交任意次数。
