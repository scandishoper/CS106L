/*
 * CS106L 作业 1：SimpleEnroll
 * 创建者：Fabio Ibanez；Jacob Roberts-Baca 修改。
 *
 * 本文件包含实现作业时可能用到的工具函数。无需修改任何内容，
 * 但可以自由阅读。
 */

/**
 * 一些重要函数的前置声明。无需理解这些内容，除非你确实感兴趣。
 */
bool operator==(const Course& lhs, const Course& rhs);
std::ostream& operator<<(std::ostream& os, const Course& course);

/**
 * 按分隔符拆分字符串，并返回拆分结果组成的向量。
 * @param s     要拆分的字符串。
 * @param delim 分隔符。
 * @returns     拆分后的字符串向量。
 */
std::vector<std::string> split(const std::string& s, char delim) {
  std::vector<std::string> return_vec;
  std::stringstream ss(s);
  std::string token;
  while (std::getline(ss, token, delim)) {
    return_vec.push_back(token);
  }
  return return_vec;
}

/**
 * 从课程向量中删除一个 Course。
 * @param v    课程向量。
 * @param elem 要删除的课程。
 *
 * 第 3 周和第 5 周会进一步学习本函数中的原理。
 */
void delete_elem_from_vector(std::vector<Course>& v, const Course& elem) {
  std::vector<Course>::iterator it = std::find(v.begin(), v.end(), elem);
  v.erase(it);
}

/**
 * 打印课程向量，用于调试。
 * @param vector_of_courses 要打印的课程向量。
 */
void print_courses(const std::vector<Course>& vector_of_courses) {
  for (const Course& course : vector_of_courses) {
    std::cout << course << std::endl;
  }
}

/* ========================================================================= *
 * 无需关注此处之后的内容。                                                  *
 * （除非你非常好奇。）                                                      *
 * ========================================================================= */

bool operator==(const Course& lhs, const Course& rhs) {
  return lhs.title == rhs.title && lhs.number_of_units == rhs.number_of_units &&
         lhs.quarter == rhs.quarter;
}

std::ostream& operator<<(std::ostream& os, const Course& course) {
  os << course.title << "," << course.number_of_units << "," << course.quarter;
  return os;
}

template <typename T>
concept is_valid_course = requires(T t) {
  { T{"Standard C++ Programming", "1", "2023-2024 Winter"} };
  std::is_same_v<T, Course>;
};

int
run_autograder()
{
  auto run_program = [](std::string program,
                        std::initializer_list<std::string> args,
                        bool silent = false) {
    std::stringstream ss;

    ss << program;
    for (const auto& arg : args) {
      ss << ' ' << arg;
    }

    if (silent) {
#ifdef _WIN32
      ss << " >nul 2>&1";
#else
      ss << " >/dev/null 2>&1";
#endif
    }

    std::cout.flush();
    return system(ss.str().c_str());
  };

  std::string python;
  for (const auto& option :
       { "python", "python3", "/usr/bin/python3", "/usr/bin/python" }) {
    if (run_program(option, { "--version" }, true) == 0) {
      python = option;
      break;
    }
  }

  if (python.empty()) {
    std::cerr
      << "Python was not found on your system. Please install Python and "
                 "try again."
              << "\n";
    std::exit(1);
  }

  return run_program(python, { "autograder/autograder.py" });
}
