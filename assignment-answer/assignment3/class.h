#ifndef CLASS_HHH
#define CLASS_HHH

#include <string>
#include <vector>

template <typename T>
class shoper {
private:
    std::string name;
    T balance;
    std::vector<T> history;
    void normalizebalance();
public:
    shoper();
    shoper(const std::string& name_, T balance_);
    std::string getname() const;
    void setname(const std::string& name_);
    T getbalance() const;
    void setbalance(T value);
    std::size_t gethistorysize() const;
};

#include "class.tpp"

#endif