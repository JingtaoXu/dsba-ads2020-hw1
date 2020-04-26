//
// Created by XuJingtao on 2020/3/31.
//

#ifndef BIG_HW_1_NUMBER_H
#define BIG_HW_1_NUMBER_H
#include<iostream>
#include<string>
#include<iomanip>
#include<algorithm>
#include<deque>


class Number
{
protected:
    std::string _num;    // control the length
    int _len;       // the length of big numb

public:
    Number()= default;   // default constructor
    Number(const std::string& str) : _num(str), _len(str.length()) {};       // constructor with string

    Number& operator= (const Number& n);   // assignment operator

    friend std::ostream& operator<< (std::ostream& out,  Number& b);

    Number operator+(const Number& rhv) const;
    Number operator-(const Number& rhv) const;

    bool operator>(const Number& rhv)const;
    bool operator==(const Number& rhv) const;
    bool operator!=(const Number& rhv) const;

public:
    std::string invert(std::string& src) const;
    std::string deZero(const std::string& str) const;
    static void addPrezero(std::string& s, int l)
    {
        for (int i = 0; i < l; i++)
            s = s.insert(0, "0");
    }
//    static Number addLastzero(Number& s, unsigned int l);
    void addLastzero(unsigned int l)
    {
        for (unsigned int i = 0; i < l; i++)
        {
            _num += "0";
            _len++;
        }
    }
    static int largerLength(Number& n1, Number& n2);


public:
    void print() const { std::cout << _num; }   // print out the Numberber
    int getLen() const { return int(_len); }
    std::string getStrNum() const { return _num ; }
};




#endif //BIG_HW_1_NUMBER_H
