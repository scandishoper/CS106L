/*
 * CS106L 作业 6：Explore Courses
 * 创建者：Haven Whitney；Jacob Roberts-Baca 与 Fabio Ibanez 修改。
 */

#include <algorithm>
#include <type_traits>
#include <vector>

/** STUDENT_TODO：需要在这里包含相关头文件。 */

#include "autograder/utils.hpp"

/**
 * 一门课程；你应该已经在作业 1 中见过它。
 */
struct Course
{
  std::string title;
  std::string number_of_units;
  std::string quarter;

  /**
   * 现在无需再忽略这里：我们正在为 Course 结构体定义 == 运算符。
   */
  bool operator==(const Course& other) const
  {
    return title == other.title && number_of_units == other.number_of_units &&
           quarter == other.quarter;
  }
};

class CourseDatabase
{
public:
  CourseDatabase(std::string filename)
  {
    auto lines = read_lines(filename);
    std::transform(lines.begin(),
                   lines.end(),
                   std::back_inserter(courses),
                   [](std::string line) {
                     auto parts = split(line, ',');
                     return Course{ parts[0], parts[1], parts[2] };
                   });
  }

  /**
   * 在数据库中查找具有给定名称的课程（如果存在）。
   * @param course_title 要查找的课程名称。
   * @return 返回类型需要由你确定。
   */
  FillMeIn find_course(std::string course_title)
  {
    /* STUDENT_TODO：实现此函数，并修改返回类型。 */
  }

private:
  std::vector<Course> courses;
};

int
main(int argc, char* argv[])
{
  static_assert(
    !std::is_same_v<std::invoke_result_t<decltype (&CourseDatabase::find_course), 
                      CourseDatabase, std::string>,
                    FillMeIn>,
    "You must change the return type of CourseDatabase::find_course to "
    "something other than FillMeIn.");

  if (argc == 2) {
    CourseDatabase db("autograder/courses.csv");
    auto course = db.find_course(argv[1]);
    
    /******************************************************** 
    STUDENT_TODO：使用要打印的正确信息填充 output 字符串。
    请特别留意 README 中的说明。
    ********************************************************/

    std::string output = /* STUDENT_TODO */

    /********************************************************
     请勿修改此行以下的任何内容。
    ********************************************************/

    std::cout << output << std::endl;
    return 0;
  }
  
  return run_autograder();
}
