template <typename T>
shoper<T>::shoper() : name("unknown"), balance{} {}

template <typename T>
shoper<T>::shoper(const std::string& name_, T balance_) : name(name_), balance(balance_) {
    normalizebalance();
}

template <typename T>
void shoper<T>::normalizebalance() {
    if (balance < T{}) {
        balance = T{};
    }
}

template <typename T>
std::string shoper<T>::getname() const {
    return name;
}

template <typename T>
T shoper<T>::getbalance() const  {
    return balance;
}

template <typename T>
void shoper<T>::setname(const std::string& name_) {
    name = name_;
}

template <typename T>
void shoper<T>::setbalance(T value) {
    balance = value;
    normalizebalance();
}

template <typename T>
std::size_t shoper<T>::gethistorysize() const {
    return history.size();
}

