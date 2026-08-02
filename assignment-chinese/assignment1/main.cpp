/*
 * CS106L 作业 1：SimpleEnroll
 * 创建者：Fabio Ibanez；Jacob Roberts-Baca 修改。
 *
 * 欢迎完成 CS106L 作业 1！请完成本文件中的每一处 STUDENT TODO，
 * 无需修改其他文件。
 *
 * 学生必须实现：parse_csv、write_courses_offered、
 * write_courses_not_offered
 */

#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

const std::string COURSES_OFFERED_PATH = "student_output/courses_offered.csv";
const std::string COURSES_NOT_OFFERED_PATH = "student_output/courses_not_offered.csv";

/**
 * 表示学生可以在 ExploreCourses 中选择的一门课程。
 * 你必须补全此结构体各字段的类型。
 * 提示：还记得 C++ 流处理什么类型吗？
 */
struct Course {
  /* STUDENT TODO：补全类型 */ title;
  /* STUDENT TODO：补全类型 */ number_of_units;
  /* STUDENT TODO：补全类型 */ quarter;
};

/**
 * （STUDENT TODO）查看本文件底部的 main 函数如何调用 parse_csv、
 * write_courses_offered 和 write_courses_not_offered。修改这些函数的签名，
 * 使其按预期工作，然后删除本段注释。
 */

/**
 * 注意：
 * 必须先声明上面的 Course 结构体，再 #include utils.cpp，
 * 这样 utils.cpp 中的代码才能识别 Course。
 * 请记住，#include 实际上会复制并粘贴文件内容。
 */
#include "utils.cpp"

/**
 * 本函数应使用 Course 类型的结构体填充 courses 向量。
 * 每个结构体都来自 courses.csv 中的一条记录，而每一行就是一条记录。
 *
 * 提示：
 * 1）查看 utils.cpp 中提供的 split 函数。
 * 2）每一行都是一条记录！这一点很重要，所以再强调一次。
 * 3）CSV 第一行定义列名，可以将其忽略。
 *
 * @param filename 要解析的文件名。
 * @param courses  待填充的课程向量。
 */
void parse_csv(std::string filename, std::vector<Course> courses) {
  /* STUDENT TODO：在此编写代码。 */
}

/**
 * 本函数有两个要求。
 *
 * 1）把已开设课程写入文件
 * "student_output/courses_offered.csv"
 *
 * 2）从 all_courses 向量中删除已开设课程。
 * 重要：必须先写入文件，再执行删除。
 *
 * 提示：
 * 1）记录需要删除的课程。
 * 2）使用提供的 delete_elem_from_vector 函数。
 * 3）记得在输出开头写入 CSV 列名，可参考 courses.csv。
 *
 * @param all_courses 调用 parse_csv 后得到的全部课程向量；
 *                    函数会从中移除所有已开设课程。
 */
void write_courses_offered(std::vector<Course> all_courses) {
  /* STUDENT TODO：在此编写代码。 */
}

/**
 * 本函数把未开设课程写入文件
 * "student_output/courses_not_offered.csv".
 *
 * 本函数始终在 write_courses_offered 之后调用。由于已在
 * write_courses_offered 中从 all_courses 删除所有已开设课程，
 * unlisted_courses 自然只包含未开设课程。
 *
 * 提示：实现方式应与 write_courses_offered 非常相似。
 *
 * @param unlisted_courses 未开设课程组成的向量。
 */
void write_courses_not_offered(std::vector<Course> unlisted_courses) {
  /* STUDENT TODO：在此编写代码。 */
}

int main() {
  /* 确认 Course 结构体定义正确。 */
  static_assert(is_valid_course<Course>, "Course struct is not correctly defined!");

  std::vector<Course> courses;
  parse_csv("courses.csv", courses);

  /* 调试时可取消下一行的注释。 */
  // print_courses(courses);

  write_courses_offered(courses);
  write_courses_not_offered(courses);

  return run_autograder();
}
