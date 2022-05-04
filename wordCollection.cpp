#include "wordCollection.h"
#include <cstring>

int hash(char symbol) {
    if (symbol >= 'a' && symbol <= 'z')
        return symbol - 87;
    else if (symbol >= 'A' && symbol <= 'Z')
        return symbol - 29;
    return symbol - '0';
}

void wordCollection::free() {
    for (int i = 0; i < SYMBOLS; i++)
        delete[] words[i];
}

void wordCollection::copyFrom(const wordCollection &other) {
    this->free();

    for (int i = 0; i < SYMBOLS; i++) {
        words[i] = new MyString[other.capacity[i]];
        capacity[i] = other.capacity[i];

        for (int j = 0; j < other.capacity[i]; j++) {
            words[i][j] = other.words[i][j];
        }
    }
}

wordCollection::wordCollection() {
    for (int i = 0; i < SYMBOLS; i++) {
        this->words[i] = new MyString[8];
        this->capacity[i] = 0;
    }
}

wordCollection::~wordCollection() {
    this->free();
}

wordCollection::wordCollection(const wordCollection &other) {
    if (this != &other) {
        this->free();
        this->copyFrom(other);
    }
}

wordCollection &wordCollection::operator=(const wordCollection &other) {
    if (this != &other) {
        this->free();
        this->copyFrom(other);
    }
    return *this;
}

void wordCollection::extendCapacity(const int row) {
    MyString *temp = new MyString[capacity[row] * 2];
    for (int i = 0; i < capacity[row]; i++)
        temp[i] = words[row][i];
    words[row] = temp;
    delete[] temp;
    capacity[row] *= 2;

}

void wordCollection::sort(const int row) {
    for (int i = 0; i < capacity[row]; i++) {
        int minIndex = i;
        for (int j = i + 1; j < capacity[row]; j++) {
            if (strcmp(words[row][minIndex].c_str(), words[row][j].c_str()) < 0)
                minIndex = j;
        }
        if (minIndex == i)
            continue;
        MyString temp = words[row][minIndex];
        words[row][minIndex] = words[row][i];
        words[row][i] = temp;
    }
}

wordCollection &wordCollection::operator*=(const MyString &str) {
    if (binarySearch(str) != -1)
        return *this;
    const int row = hash(str[0]);
    if (sizeof(*words[row]) / sizeof(MyString) == capacity[row])
        this->extendCapacity(row);
    words[row][capacity[row]] = str;
    capacity[row]++;
    this->sort(row);
    return *this;
}

wordCollection &wordCollection::operator+=(const wordCollection &other) {
    if (this == &other)
        return *this;
    for (int i = 0; i < SYMBOLS; i++)
        for (int j = 0; j < other.capacity[i]; i++)
            *this *= other.words[i][j];
    return *this;
}

wordCollection &wordCollection::operator/=(const MyString &str) {
    const int row = hash(str[0]);
    int index = binarySearch(str);
    if (index == -1)
        return *this;
    for (int i = index; i < capacity[row] - 1; i++)
        words[row][i] = words[row][i + 1];
    capacity[row]--;
    return *this;
}

bool wordCollection::operator[](const MyString &other) {
    int index = binarySearch(other);
    if (index == -1)
        return false;
    return true;
}

wordCollection &wordCollection::operator-=(const wordCollection &other) {
    for (int i = 0; i < SYMBOLS; i++) {
        for (int j = 0; j < other.capacity[i]; j++)
            *this /= other.words[i][j];
    }
    return *this;
}

std::ostream &operator<<(std::ostream &out, const wordCollection &collection) {
    for (int i = 0; i < SYMBOLS; i++) {
        for (int j = 0; j < collection.capacity[i]; j++)
            out << collection.words[i][j] << " ";
    }
    return out;
}

std::istream &operator>>(std::istream &in, wordCollection &collection) {
    MyString temp;
    in >> temp;
    collection *= temp;
    return in;
}

int wordCollection::binarySearch(const MyString &other) {
    const int row = hash(other[0]);
    int start = 0, end = capacity[row] - 1;
    while (start <= end) {
        int mid = (end - start) / 2;
        int cmpRes = strcmp(other.c_str(), words[row][mid].c_str());
        if (!cmpRes)
            return mid;
        else if (cmpRes < 0)
            end = mid - 1;
        else
            start = mid + 1;
    }
    return -1;
}
