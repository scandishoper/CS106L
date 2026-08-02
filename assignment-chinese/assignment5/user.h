/*
 * CS106L 作业 5：TreeBook
 * 创建者：Fabio Ibanez；Jacob Roberts-Baca 修改。
 */

#include <iostream>
#include <string>

class User
{
public:
  User(const std::string& name);
  void add_friend(const std::string& name);
  std::string get_name() const;
  size_t size() const;
  void set_friend(size_t index, const std::string& name);

  /** 
   * STUDENT TODO：
   * 在这里声明自定义运算符和特殊成员函数。
   */

private:
  std::string _name;
  std::string* _friends;
  size_t _size;
  size_t _capacity;
};
