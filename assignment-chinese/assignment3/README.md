<p align="center">
  <img src="docs/bjarne.jpg" alt="Bjarne Stroustrup 在白板上书写类声明" />
</p>

# 作业 3：创建一个类

截止时间：5 月 1 日（星期五）23:59

## 概述

<pre>
(\_/)
(•x•) <b>你好</b>
(<☕)
</pre>

学习类之后，现在该亲手创建一个了！尽情发挥创意：你的类可以表示任何事物，也可以根据兴趣创建多个类。只要满足下列要求，就能完成本作业 🙂。

本作业需要处理四个文件：

- `class.h`：类的头文件，用于编写类的**声明**。
- `class.cpp`：类的 `.cpp` 文件，用于编写类的成员函数**定义**。
- `sandbox.cpp`：在这里构造类的实例。
- `short_answer.txt`：在这里回答简答题。

开始前，请先按照[环境配置说明](../assignment-setup/README.md)下载并配置起始代码。

## 运行代码

打开终端（VSCode 中可按 <kbd>Ctrl+`</kbd>，或选择 **Terminal > New Terminal**），确认当前位于 `assignment3/` 目录，然后编译：

```sh
g++ -std=c++20 main.cpp class.cpp -o main
```

如果编译没有报错，请运行 `./main`。建议在完成下述步骤时经常编译并运行自动评分器。

> [!NOTE]
>
> ### Windows 用户说明
>
> Windows 上可能需要使用以下命令编译：
>
> ```sh
> g++ -static-libstdc++ -std=c++20 main.cpp class.cpp -o main
> ```
>
> 生成的文件也可能名为 `main.exe`，此时请运行 `./main.exe`。

## 第 1 部分：创建你的类

在 `class.h` 和 `class.cpp` 中创建一个自定义类。可以参考周二关于类的课程幻灯片。类可以表示几乎任何事物，但必须满足以下要求。

> [!IMPORTANT]
>
> ### 类的要求
>
> 你的类必须：
>
> 1. 提供一个接收**至少一个**参数的自定义构造函数。
> 2. 提供一个默认（无参）构造函数，即实现构造函数重载。
> 3. 至少包含一个私有成员字段（变量）。
> 4. 至少包含一个私有成员函数。
>    - 私有函数就像汽车内部的工作机制：它是类实现所必需的，但不应暴露在公开接口中。请设计一个符合类本身语义的私有成员函数。
> 5. 至少为一个私有字段提供公开的 getter 函数。
>    - 例如，字段为 `int data` 时，必须提供名为 `get_data` 或 `getData`、签名如下的函数：<pre lang="cpp">int getData();</pre>
>    - getter 还应标记为 `const`。如果不熟悉，请回顾周四关于 `const` 正确性的课程。
> 6. 至少为一个私有字段提供公开的 setter 函数。
>    - 例如，字段为 `int data` 时，应提供名为 `set_data` 或 `setData`、签名如下的函数：<pre lang="cpp">void setData(int value);</pre>

以上只是获得作业成绩的最低要求。你可以添加更多功能，或创建多个类来获得额外练习。

> [!NOTE]
> 如果想挑战自己，可以使用周四课程介绍的 `template <typename T>` 语法创建类模板，而不是普通类。这完全是可选项。
>
> 如果使用类模板，**必须从编译命令中移除 `class.cpp`**。例如，macOS/Linux 上的命令应改为：
>
> ```sh
> g++ -std=c++20 main.cpp -o main
> ```
>
> 同时请按照周四课程所讲，在 `.h` 文件末尾包含 `.cpp` 文件，并相应调整 `#include`。

创建类以后，需要真正使用它。**请在 `sandbox.cpp` 的 `sandbox` 函数中构造一个类实例。**构造方式不限，例如调用默认构造函数或使用统一初始化。

完成后编译并运行代码。自动评分器会检查类是否满足上述要求，并提供反馈。

## 第 2 部分：简答题

请在 `short_answer.txt` 中回答以下问题，每题约 2～3 句话。

> [!IMPORTANT]
>
> ### `short_answer.txt`
>
> - **问题 1：**什么是 `const` 正确性？它为什么重要？
> - **问题 2：**你的类满足 `const` 正确性吗？如何判断？

## 🚀 提交说明

提交步骤：

1. 填写[反馈表](https://forms.gle/GmhzW9NycQ44hyF86)。
2. 在 [Paperless](https://paperless.stanford.edu) 上提交作业。

需要提交：

- `class.h`
- `class.cpp`
- `sandbox.cpp`
- `short_answer.txt`

截止时间前可以重复提交任意次数。
