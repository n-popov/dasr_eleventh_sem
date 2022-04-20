#include <iostream>
#include <iomanip>

struct Date {
    Date(int year, int month, int day):
        year(year), month(month), day(day) {}

    int year, month, day;
};

std::ostream& operator<<(std::ostream& out, Date d) {
    return out << d.year << '.' << std::setfill('0') << std::setw(2) <<
        d.month << '.' << std::setw(2) << d.day;
}

template<typename T>
class smart_ptr {
public:
    template<typename ...Types>
    smart_ptr(Types ...args) : ptr(new T(args...)) {}

    smart_ptr(const smart_ptr<T>&) = delete;
    smart_ptr& operator=(const smart_ptr<T>&) = delete;

    T &operator*() {
        return *ptr;
    }

    ~smart_ptr() {
        delete ptr;
    }

    template <typename K>
    friend std::ostream& operator<<(std::ostream&, const smart_ptr<K>&);

private:
    T *ptr;
};

template<typename K>
std::ostream& operator<<(std::ostream& out, const smart_ptr<K>& smart_ptr) {
    return out << smart_ptr.ptr;
}


struct IntWrapper {
    explicit IntWrapper(int value): wrapped(value) {}
    int wrapped;
};

IntWrapper wrap(int value) {
    return IntWrapper(value);
}


int main() {
//    auto p_int = smart_ptr<int>(5);
//    std::cout << *p_int << std::endl;
//    *p_int = 7;
//    std::cout << *p_int << std::endl;

    auto p_int = smart_ptr<Date>(2022, 4, 15);
    std::cout << *p_int << std::endl;
    *p_int = Date(2022, 4, 14);
    std::cout << *p_int << std::endl;
    std::cout << p_int << std::endl;
    return EXIT_SUCCESS;
}
