<p align="center">
  <img src="docs/marriage_pact.png" alt="Marriage Pact 标志" />
</p>

# 作业 2：Marriage Pact

截止时间：4 月 24 日（星期五）23:59

## 概述

欢迎来到作业 2！这是一份短小的练习，帮助你开始使用 STL 容器与指针。

你需要关注以下文件：

- `main.cpp`：你的所有代码都写在这里 😀。
- `short_answer.txt`：简答题答案写在这里 📝。

开始前，请先按照[环境配置说明](../assignment-setup/README.md)下载并配置起始代码。

## 运行代码

打开终端（VSCode 中可按 <kbd>Ctrl+`</kbd>，或选择 **Terminal > New Terminal**），确认当前位于 `assignment2/` 目录，然后编译：

```sh
g++ -std=c++20 main.cpp -o main
```

如果编译没有报错，请运行：

```sh
./main
```

这会执行 `main.cpp` 中的 `main` 函数。建议在完成下述步骤时经常编译并运行自动评分器，以便及时确认方向是否正确。

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

## 第 0 部分：准备工作

欢迎参加 Marriage Pact！开始前需要知道你的姓名。请把 `main.cpp` 顶部的常量 `kYourName` 从 `"STUDENT TODO"` 修改为你的全名，名与姓之间保留一个空格。

## 第 1 部分：获取全部申请者

你已经等了好几天，今年的 Marriage Pact 姓名首字母终于发到了邮箱！今年新增了一条规则：匹配对象必须与你拥有相同的姓名首字母。但校园里有数千名学生，手工遍历名单寻找潜在匹配对象显然不现实。好在你正在学习 CS106L，而 C++ 恰好提供了快速处理同类数据集合的工具——容器。

仓库提供了 `students.txt`，其中列出今年报名 Marriage Pact 的所有虚构学生。每行包含一名学生的名和姓。首先实现 `get_applicants`：

> [!IMPORTANT]
>
> ### `get_applicants`
>
> 从 `.txt` 文件中解析全部姓名并存入集合。文件 `filename` 的每一行都是一名申请者的姓名。你可以自由选择有序集合 `std::set` 或无序集合 `std::unordered_set`；如果选择无序集合，请同步修改相关函数声明。

然后在 `short_answer.txt` 中回答：

> [!IMPORTANT]
>
> ### `short_answer.txt`
>
> **问题 1：**你可以选择有序集合或无序集合。请用几句话说明两者的取舍，并给出一个课堂上没有讲过、可用于在无序集合中对学生姓名进行哈希的有效哈希函数示例。

> [!NOTE]
> 本作业出现的所有姓名均为虚构；如与现实人物相似，纯属巧合。

## 第 2 部分：寻找匹配对象

经过前面的筛选，潜在对象范围已经缩小。现在需要实现一个函数，自动整理与自己首字母相同的候选人访问顺序。本部分要编写 `find_matches` 和 `get_match`。

> [!IMPORTANT]
>
> ### `find_matches`
>
> 从上一部分生成的 `students` 集合中找出所有与参数 `name` 具有相同首字母的姓名，并把指向这些姓名的指针放入一个新的 `std::queue`。

- 如果不确定如何遍历集合，可以回顾[周四关于迭代器和指针的课程](https://office365stanford-my.sharepoint.com/:p:/g/personal/jtrb_stanford_edu/EbOKUV784rBHrO3JIhUSAUgBvuIGn5rSU8h3xbq-Q1JFfQ?e=BlZwa7)。
- 本部分需要熟悉 `std::queue` 的操作，可查阅 [cppreference 文档](https://en.cppreference.com/w/cpp/container/queue)。
- 提示：可以定义一个辅助函数来计算学生姓名的首字母，然后比较 `name` 与 `students` 中每个姓名的首字母。

接下来实现 `get_match`，找出你的“唯一真爱”：

> [!IMPORTANT]
>
> ### `get_match`
>
> 从所有潜在匹配对象组成的队列中选出一人。具体选择规则由你决定；最好比简单调用一次 `pop()` 多一点设计，但不需要特别复杂，可以考虑随机数或其他选取方式。
>
> 如果数据集中没有与你首字母相同的人，请输出 `"NO MATCHES FOUND."`。明年再接再厉 😢

最后在 `short_answer.txt` 中回答：

> [!IMPORTANT]
>
> ### `short_answer.txt`
>
> **问题 2：**队列中保存的是指向姓名的指针，而不是姓名本身。这样做在本题中可能有什么好处？如果存储姓名的原始集合离开作用域后仍解引用这些指针，会发生什么？

## 🚀 提交说明

提交步骤：

1. 填写[反馈表](https://forms.gle/Zv27LwmtCPz88Kg46)。
2. 在 [Paperless](https://paperless.stanford.edu) 上提交作业。

需要提交：

- `main.cpp`
- `short_answer.txt`

截止时间前可以重复提交任意次数。
