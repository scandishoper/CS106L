/*
 * CS106L 作业 2：Marriage Pact
 * 创建者：Haven Whitney；Fabio Ibanez 与 Jacob Roberts-Baca 修改。
 *
 * 欢迎完成 CS106L 作业 2！请完成本文件中的每一处 STUDENT TODO，
 * 无需修改其他文件。
 *
 */

#include <fstream>
#include <iostream>
#include <queue>
#include <set>
#include <string>
#include <unordered_set>

std::string kYourName = "STUDENT TODO"; // 不要忘记修改这里。

/**
 * 接收文件名，返回包含所有申请者姓名的集合。
 *
 * @param filename  要读取的文件名；文件每一行是一名申请者的姓名。
 * @returns         从文件中读取的全部申请者姓名集合。
 *
 * @remark 可以把本函数及其下方函数的返回类型改为 std::unordered_set。
 * 如果这样做，请同时修改 utils.h 中的对应函数。
 */
std::set<std::string> get_applicants(std::string filename) {
  // STUDENT TODO：实现此函数。
}

/**
 * 按引用接收学生姓名集合，返回与给定姓名匹配的姓名队列。
 *
 * @param name      返回队列中的姓名应与该姓名具有相同首字母。
 * @param students  学生姓名集合。
 * @return          包含每个匹配姓名指针的队列。
 */
std::queue<const std::string*> find_matches(std::string name, std::set<std::string>& students) {
  // STUDENT TODO：实现此函数。
}

/**
 * 接收潜在匹配对象的指针队列，并选出唯一匹配对象。
 *
 * 实现方式不限，但请尝试比简单调用 pop() 稍微复杂一些的方法。
 *
 * @param matches 潜在匹配对象队列。
 * @return        选中的唯一匹配对象；matches 为空时返回
 *                "NO MATCHES FOUND."。
 */
std::string get_match(std::queue<const std::string*>& matches) {
  // STUDENT TODO：实现此函数。
}

/* #### 请勿删除此行。 #### */
#include "autograder/utils.hpp"
