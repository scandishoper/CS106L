#include "user.h"

/**
 * Creates a new User with the given name and no friends.
 */
User::User(const std::string& name)
  : _name(name)
  , _friends(nullptr)
  , _size(0)
  , _capacity(0)
{
}

/**
 * Adds a friend to this User's list of friends.
 * @param name The name of the friend to add.
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
 * Returns the name of this User.
 */
std::string
User::get_name() const
{
  return _name;
}

/**
 * Returns the number of friends this User has.
 */
size_t
User::size() const
{
  return _size;
}

/**
 * Sets the friend at the given index to the given name.
 * @param index The index of the friend to set.
 * @param name The name to set the friend to.
 */
void User::set_friend(size_t index, const std::string& name)
{
  _friends[index] = name;
}

/** 
 * STUDENT TODO:
 * The definitions for your custom operators and special member functions will go here!
 */
std::ostream& operator<< (std::ostream& out, const User& user) {
    out << "User(name=" << user._name << ", friends=[";
    for (size_t i = 0; i < user._size; i++) {
        if (i) out << ", " << user._friends[i];
        else out << user._friends[i];
    }
    out << "])";
    return out;
}

User::~User() {
	delete[] _friends;
}

User::User(const User& user) : _name(user._name), _size(user._size), _capacity(user._capacity) {
	_friends = _capacity == 0 ? nullptr : new std::string[_capacity];
	for (size_t i = 0; i < _size; i++) {
		_friends[i] = user._friends[i];
	}
}

User& User::operator= (const User& user) {
	_name = user._name;
	_size = user._size;
	_capacity = user._capacity;
	std::string* new_friend = _capacity == 0 ? nullptr : new std::string[_capacity];
	for (size_t i = 0; i < _size; i++) {
		new_friend[i] = user._friends[i];
	}
	delete[] _friends;
	_friends = new_friend;
	return *this;
}

User& User::operator+= (User& user) {
	add_friend(user._name);
	user.add_friend(_name);
	return *this;
}

bool User::operator< (const User& user) const {
	return _name < user._name;
}