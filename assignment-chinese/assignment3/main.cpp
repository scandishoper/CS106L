/*
 * CS106L 作业 3：创建一个类
 * 创建者：Fabio Ibanez；Jacob Roberts-Baca 修改。
 */

/* ========================================================================= *
 * 无需关注此处之后的内容。                                                  *
 * （除非你非常好奇。）                                                      *
 * ========================================================================= */

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "sandbox.cpp"

int run_autograder() {
  auto run_program = [](std::string program, std::initializer_list<std::string> args,
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
  for (const auto& option : {"python", "python3", "/usr/bin/python3", "/usr/bin/python"}) {
    if (run_program(option, {"--version"}, true) == 0) {
      python = option;
      break;
    }
  }

  if (python.empty()) {
    std::cerr << "Python was not found on your system. Please install Python and "
                 "try again."
              << "\n";
    std::exit(1);
  }

  return run_program(python, {"autograder/autograder.py"});
}

int main() {
    sandbox();
    return run_autograder();
}
