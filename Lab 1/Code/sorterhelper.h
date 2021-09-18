#ifndef SORTERHELPER_H
#define SORTERHELPER_H

#include <vector>
#include "Sorter.h"

class sorterHelper
{
private:
    Sorter<int> *exp[5];
    int algorithms[5];

public:
    sorterHelper();
    ~sorterHelper();
    void test1();
    void test2(int, int);
    void test3(int[]);
    void test4(int, int);
    void setAlgorithms(int, int);
    void output();
};

#endif // SORTERHELPER_H
