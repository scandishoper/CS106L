#include "user.h"

/**
 * 创建一个具有给定姓名、尚无好友的新 User。
 */
User::User(const std::string& name)
  : _name(name)
  , _friends(nullptr)
  , _size(0)
  , _capacity(0)
{
}

/**
 * 向该 User 的好友列表中添加好友。
 * @param name 要添加的好友姓名。
 */
void
User::add_friend(const std::string& name)
{
  if (_size == _capacity) {
    _capacity = 2 * _capacity + 1;
    std::string* newFriends = new std::string[_capacity];
    for (size_t i = 0; i < _size; ++i) {
      newFriends[i] = _friends[i];
    }
    delete[] _friends;
    _friends = newFriends;
  }

  _friends[_size++] = name;
}

/**
 * 返回该 User 的姓名。
 */
std::string
User::get_name() const
{
  return _name;
}

/**
 * 返回该 User 的好友数量。
 */
size_t
User::size() const
{
  return _size;
}

/**
 * 把指定下标处的好友设为给定姓名。
 * @param index 要修改的好友下标。
 * @param name  要设置的好友姓名。
 */
void User::set_friend(size_t index, const std::string& name)
{
  _friends[index] = name;
}

/** 
 * STUDENT TODO：
 * 在这里定义自定义运算符和特殊成员函数。
 */
