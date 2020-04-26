//
// Created by XuJingtao on 2020/4/7.
//

#ifndef BIG_HW_1_MULTIPLICATOR_H
#define BIG_HW_1_MULTIPLICATOR_H

#include "Number.h"
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <algorithm>
#include <string>
#include <vector>
#include <cstring>
#include <fstream>
#include <random>
#include <sstream>
#include<deque>

class Multiplicator
{
public:
    virtual ~Multiplicator(){}

public:
    virtual Number mult(const Number& n1, const Number& n2) const = 0;

public:
    ///task 2
    static std::string genNum();
    static std::string genNum_noZero();
    static std::string genRandom(size_t k); // generates a random number of k-digits
    ///task 3 auxiliary methods
    static Number sumAllProd(std::vector<Number> v); // sum up all products in the GradeSchool
    static std::pair<Number, Number> split2Halves(const Number& x, int largerL);
};

class GradeSchool : public Multiplicator
{
public:
    virtual Number mult(const Number& n1, const Number& n2) const override ;
};

class DivideAndConquer : public Multiplicator
{
public:
    virtual Number mult(const Number& n1, const Number& n2) const override ;
};

class Karatsuba : public Multiplicator
{
public:
    virtual Number mult(const Number& n1, const Number& n2) const override ;
};


#endif //BIG_HW_1_MULTIPLICATOR_H
