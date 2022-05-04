#include "myString.h"

const short SYMBOLS = 62;

class wordCollection {
    MyString *words[SYMBOLS]{};
    int capacity[SYMBOLS]{};

    void copyFrom(const wordCollection &other);

    void free();

public:
    wordCollection();

    wordCollection(const wordCollection &other);

    wordCollection &operator=(const wordCollection &other);

    ~wordCollection();

    wordCollection &operator*=(const MyString &other);

    void extendCapacity(int row);

    void sort(int row);

    wordCollection &operator+=(const wordCollection &other);

    wordCollection &operator-=(const wordCollection &other);

    wordCollection &operator/=(const MyString &other);

    bool operator[](const MyString &other);

    int binarySearch(const MyString &other);

    friend std::ostream &operator<<(std::ostream &out, const wordCollection &other);

    friend std::istream &operator>>(std::istream &in, wordCollection &other);
};

