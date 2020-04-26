//
// Created by XuJingtao on 2020/4/7.
//

#include "Multiplicator.h"

std::string Multiplicator::genNum()
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(0, 9);
    return std::to_string(dis(gen));
}

std::string Multiplicator::genNum_noZero()
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(1, 9);
    return std::to_string(dis(gen));
}

std::string Multiplicator::genRandom(size_t k)
{
    std::string s;
    for (unsigned int i = 0; i < k - 1; ++i)
    {
        s += genNum();
    }
    s = genNum_noZero() + s;
    return s;
}

std::pair<Number, Number> Multiplicator::split2Halves(const Number& x, int largerL)
{
    unsigned int leftHalf = largerL/2; // first half, floor(n/2)
    unsigned int rightHalf = (largerL - leftHalf); // second half, ceil(n/2)

    std::pair<Number, Number> res;

    res.first = Number(x.getStrNum().substr(0, leftHalf));
    res.second = Number(x.getStrNum().substr(leftHalf, rightHalf));
    return res;
}

Number Multiplicator::sumAllProd(std::vector<Number> v)
{
    Number sum = v[0];
    for (int i = 1; i < v.size(); ++i)
    {
        sum = sum + v[i];
    }
    return sum;
}

/// GradeSchool multiplication
Number GradeSchool::mult(const Number& n1, const Number& n2) const
{
    if (n1.getLen() == 1) // if it is multiplication of two numbers with one digit
        return Number(std::to_string(stoi(n1.getStrNum()) * stoi(n2.getStrNum())));

    std::string x = n1.getStrNum();
    std::string y = n2.getStrNum();

//    cout << x << "\t" << y << '\n';

    std::string res = "";
    //deque makes the procedure of carry bit a bit faster then vector(insert elements in front of the queue)
    std::deque<int> vec(x.size() + y.size() - 1, 0);

    for (int i = 0; i < x.size(); ++i)
    {
        for (int j = 0; j < y.size(); ++j)
        {
            vec[i + j] += (x[i] - '0') * (y[j] - '0');  // the records of the products
        }
    }

    //carry flag
    int addflag = 0;
    //read from the lowest bit, do the merge step
    for (int i = vec.size() - 1; i >= 0; --i)
    {
        int temp = vec[i] + addflag;
        vec[i] = temp % 10;     //current val.
        addflag = temp / 10;    //carry val.
    }

    //insert the carry val. to the front of the queue
    while (addflag != 0)
    {
        int t = addflag % 10;
        vec.push_front(t);
        addflag /= 10;
    }

    //combine all digits
    for (auto c : vec)
    {
        std::ostringstream ss;
        ss << c;
        res = res + ss.str();
    }
    Number r(res);
    return r;
}


/// DivideAndConquer multiplication
Number DivideAndConquer::mult(const Number& n1, const Number& n2) const
{
    Number x = n1;
    Number y = n2;
    int n = Number::largerLength(x, y);


    /// base case:
    if (n == 1) // if it is multiplication of two numbers with one digit
        return Number(std::to_string(stoi(x.getStrNum()) * stoi(y.getStrNum())));

    unsigned int l = n/2;
    unsigned int r = (n-l);

    std::pair<Number, Number> pairOfx = split2Halves(x, n);
    std::pair<Number, Number> pairOfy = split2Halves(y, n);

    Number x1y1 = mult(pairOfx.first,pairOfy.first);
    Number x1y2 = mult(pairOfx.first,pairOfy.second);
    Number x2y1 = mult(pairOfx.second,pairOfy.first);
    Number x2y2 = mult(pairOfx.second,pairOfy.second);


//    sum = Number::addLastzero(x1y1,r * 2)
//            + Number::addLastzero(x1y2, r)
//            + Number::addLastzero(x2y1, r)
//            + x2y2;

    x1y1.addLastzero(r * 2);
    x1y2.addLastzero(r);
    x2y1.addLastzero(r);

//    sum = x1y1 + x1y2 + x2y1 + x2y2;

    return Number(x1y1 + x1y2 + x2y1 + x2y2);;
}

/// Karatsuba multiplication
Number Karatsuba::mult(const Number& n1, const Number& n2) const
{
    Number x = n1;
    Number y = n2;
    int n = Number::largerLength(x, y);

    /// base case:
    if (n == 1) // if it is multiplication of two numbers with one digit
        return Number(std::to_string(stoi(x.getStrNum())*stoi(y.getStrNum())));

    unsigned int l = n/2;
    unsigned int r = (n-l);

    std::pair<Number, Number> pairOfx = split2Halves(x, n);
    std::pair<Number, Number> pairOfy = split2Halves(y, n);

    Number x1y1 = mult(pairOfx.first,pairOfy.first);
    Number sumX = pairOfx.first + pairOfx.second;
    Number sumY = pairOfy.first + pairOfy.second;
    Number karaTerm = mult(sumX, sumY);
    Number x2y2 = mult(pairOfx.second,pairOfy.second);

    Number midTerm = karaTerm - x1y1 - x2y2;



    x1y1.addLastzero(r * 2);
    midTerm.addLastzero(r);

//    sum = Number::addLastzero(x1y1,r * 2)
//            + Number::addLastzero(midTerm, r)
//            + x2y2;

    return  Number(x1y1 + midTerm + x2y2);
}
