#include "myString.h"
#include <cstring>

void MyString::copyFrom(const MyString &other) {
    str = new char[strlen(other.str) + 1];
    strcpy(str, other.str);
    size = other.size;
}

void MyString::free() {
    delete[] str;
}

MyString::MyString() {
    str = new char[1];
    str[0] = '\0';
    size = 0;
}

MyString::MyString(const char *data) {
    size = strlen(data);
    str = new char[size + 1];
    strcpy(str, data);
}

MyString::MyString(const MyString &other) {
    copyFrom(other);
}

MyString &MyString::operator=(const MyString &other) {
    if (this != &other) {
        free();
        copyFrom(other);
    }
    return *this;
}

MyString::~MyString() {
    free();
}

const char *MyString::c_str() const {
    return str;
}

std::ostream &operator<<(std::ostream &os, const MyString &string) {
    return os << string.str;
}

std::istream &operator>>(std::istream &is, MyString &string) {
    return is >> string.str;
}

char &MyString::operator[](int i) const {
    return str[i];
}
