/*
 * CS106L 作业 7：独占指针
 * 创建者：Jacob Roberts-Baca。
 */

#include <functional>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <vector>

#include "unique_ptr.h"

/**
 * @brief 单链表节点，使用 unique_ptr 管理指向下一节点的指针，从而自动释放自身。
 * @tparam T 节点中存储的值类型。
 *
 * @note 完成本作业无需修改此结构体。
 */
template <typename T> struct ListNode {

  /** @brief 节点中存储的值。 */
  T value;

  /** @brief 指向下一节点的智能指针，可以为空。 */
  cs106l::unique_ptr<ListNode<T>> next;

  /**
   * @brief 构造只含一个元素的链表，并把 next 设为 nullptr。
   * @param value 要存入节点的值。
   */
  ListNode(T value) : value(value), next(nullptr) {
    /* 本行只用于记录日志，方便观察构造函数何时运行。 */
    std::cout << "Constructing node with value '" << value << "'\n";
  }

  ~ListNode() {
    /* 本行只用于记录日志，方便观察析构函数何时运行。 */
    std::cout << "Destructing node with value '" << value << "'\n";
  }
};

/**
 * @brief 根据值向量创建单链表。
 * @param values 要存入链表的值。
 * @return 指向链表头节点的 unique_ptr。
 */
template <typename T> cs106l::unique_ptr<ListNode<T>> create_list(const std::vector<T>& values) {
  /* STUDENT TODO：实现此函数。 */
  throw std::runtime_error("Not implemented: createList");
}

/**
 * @brief 对链表中的每个元素应用一个函数。
 * @tparam T 链表中存储的值类型。
 * @tparam Func 要应用的函数类型。
 * @param head 链表头节点。
 * @paragraph func 要应用于每个元素的函数。
 */
template <typename T, typename Func>
void map_list(const cs106l::unique_ptr<ListNode<T>>& head, const Func& func) {
  if (!head)
    return;
  func(head->value);
  map_list(head->next, func);
}

/**
 * @brief 使用 unique_ptr 管理单链表的示例。
 */
void linked_list_example() {
  std::vector<std::string> names{"Jacob", "Fabio", "Keith", "Chris", "Sean"};
  auto head = create_list(names);
  map_list(head, [](const std::string& name) { std::cout << name << "\n"; });
}

#include "autograder/utils.hpp"
