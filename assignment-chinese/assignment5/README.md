<p align="center">
  <img src="docs/logo.jpeg" alt="虚构的斯坦福社交媒体创业公司 Treebook 的标志" style="width: 300px; height: auto;" />
</p>

# 作业 5：Treebook

截止时间：5 月 15 日（星期五）23:59

## 概述

斯坦福最新的社交媒体创业项目叫 Treebook，而你正是创始团队成员！为了让产品顺利上线，并与哈佛某款“没有任何法律关联”的应用竞争，你负责实现用户资料功能。

本作业需要完善一个类，练习运算符重载以及特殊成员函数的定制。

你会修改两个文件：

- `user.h`：包含 `User` 类的声明；你将在其中添加特殊成员函数和运算符。
- `user.cpp`：包含 `User` 类成员函数的定义。

开始前，请先按照[环境配置说明](../assignment-setup/README.md)下载并配置起始代码。

## 运行代码

打开终端（VSCode 中可按 <kbd>Ctrl+`</kbd>，或选择 **Terminal > New Terminal**），确认当前位于 `assignment5/` 目录，然后编译：

```sh
g++ -std=c++20 main.cpp user.cpp -o main
```

如果编译没有报错，请运行 `./main`。建议在完成下述步骤时经常编译并运行自动评分器。

> [!NOTE]
>
> ### Windows 用户说明
>
> Windows 上可能需要使用以下命令编译：
>
> ```sh
> g++ -static-libstdc++ -std=c++20 main.cpp user.cpp -o main
> ```
>
> 生成的文件也可能名为 `main.exe`，此时请运行 `./main.exe`。

## 第 1 部分：查看用户资料

查看头文件 `user.h`。你的同事已经开始编写 `User` 类，用于保存每位用户的姓名和好友列表。为了提高效率，他们用 `std::string` 的原始指针数组表示好友列表，这与 `std::vector` 在底层存储元素的方式有些相似。他们已经实现了创建 `User` 以及向现有用户好友列表添加好友的逻辑（`add_friend`），但在使用 `User` 对象时遇到了一些奇怪问题。

首先，目前没有便捷方式在控制台中打印 `User` 对象信息，给 Treebook 的调试工作带来了困难。请编写 `operator<<`，把 `User` 输出到 `std::ostream`。**该运算符必须在 `user.h` 中声明为友元函数，并在 `user.cpp` 中实现。**例如，名为 `"Alice"`、好友为 `"Bob"` 和 `"Charlie"` 的用户应输出：

```text
User(name=Alice, friends=[Bob, Charlie])
```

注意：`operator<<` 不应输出换行符。

> [!IMPORTANT]
> 实现 `operator<<` 时，需要访问并遍历 `User` 的私有字段 `_friends`。普通非成员函数无法访问类的私有字段；这里可以把 `operator<<` 在 `User` 类中标记为**友元函数**来解除限制。更多信息请参考周二课程幻灯片。

## 第 2 部分：不友好的行为

借助 `operator<<`，团队的开发进展很顺利。但复制内存中的 `User` 对象时仍会出现一些看似离奇的问题。学过 CS106L 的你怀疑，这与 `User` 类的特殊成员函数（或缺少这些函数）有关。为解决问题，需要自行实现部分特殊成员函数（SMF），并删除那些由编译器生成、但行为不符合要求的函数。

具体任务：

1. 实现 `User` 的析构函数 `~User()`。
2. 让 `User` 支持复制构造：实现 `User(const User& user)`。
3. 让 `User` 支持复制赋值：实现 `User& operator=(const User& user)`。
4. 禁止移动构造：删除 `User(User&& user)`。
5. 禁止移动赋值：删除 `User& operator=(User&& user)`。

这些任务需要同时修改 `user.h` 和 `user.cpp`。

> [!IMPORTANT]
> 实现第 2、3 项时，需要复制 `_friends` 数组的内容。回顾周四关于特殊成员函数的课程：复制指针数组时，应先为新数组分配内存（可以在成员初始化列表中完成），再用循环逐一复制元素。
>
> 还要确保被修改实例的 `_size`、`_capacity` 和 `_name` 都被正确设置。

## 第 3 部分：随时加好友

特殊成员函数修复后，Treebook 已经扩展到整个斯坦福，甚至开始在其他大学流行。不过团队发现，`User` 当前接口让一些常见操作很不方便，甚至无法完成。为此，需要自定义两个运算符。

请把以下两个运算符都实现为**成员函数**，即在 `user.h` 的 `User` 类中声明，并在 `user.cpp` 中定义。

### `operator+=`

`+=` 表示把一个用户加入另一个用户的好友列表。好友关系应当对称：把 Charlie 加入 Alice 的好友列表时，也应把 Alice 加入 Charlie 的好友列表。例如：

```cpp
User alice("Alice");
User charlie("Charlie");

alice += charlie;
std::cout << alice << std::endl;
std::cout << charlie << std::endl;

// 预期输出：
// User(name=Alice, friends=[Charlie])
// User(name=Charlie, friends=[Alice])
```

函数签名应为 `User& operator+=(User& rhs)`。与复制赋值运算符一样，它返回自身的引用。

### `operator<`

`std::set` 依赖比较运算符，因此要把用户存入 `std::set`，必须提供 `<`。请实现 `operator<`，按照姓名的字母顺序比较用户。例如：

```cpp
User alice("Alice");
User charlie("Charlie");

if (alice < charlie)
  std::cout << "Alice is less than Charlie";
else
  std::cout << "Charlie is less than Alice";

// 预期输出：
// Alice is less than Charlie
```

函数签名应为 `bool operator<(const User& rhs) const`。

## 🚀 提交说明

通过全部测试后即可提交：

1. 填写[反馈表](https://forms.gle/tfLJSKnuUbUx9Xdi6)。
2. 在 [Paperless](https://paperless.stanford.edu) 上提交作业。

需要提交：

- `user.h`
- `user.cpp`

截止时间前可以重复提交任意次数。
