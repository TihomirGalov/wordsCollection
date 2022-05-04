#include <iostream>

class MyString {
    char *str;
    size_t size;

    void copyFrom(const MyString &other);

    void free();

public:
    MyString();

    MyString(const char *);

    MyString(const MyString &);

    MyString &operator=(const MyString &other);

    ~MyString();

    const char *c_str() const;

    char &operator[](int i) const;

    friend std::ostream &operator<<(std::ostream &os, const MyString &str);

    friend std::istream &operator>>(std::istream &is, MyString &str);
};