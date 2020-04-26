//
// Created by XuJingtao on 2020/4/7.
//

#include <sstream>
#include "Number.h"

Number& Number::operator= (const Number& n)
{
    _num = n._num;
    _len = n._len;
    return *this;
}

std::ostream &operator<<(std::ostream& out, Number& b)
{
    out << b.getStrNum();
    return out;
}

std::string Number::invert(std::string &src) const
{
    std::string newStr=src;
    for(int i = src.length() - 1, j = 0; i >= 0; --i, ++j)
        newStr[j]=src[i];

    return newStr;
}

Number Number::operator+ (const Number& rhv) const
{
    std::string str1 = _num;
    std::string str2 = rhv._num;
    std::string res;

    reverse(str1.begin(), str1.end());
    reverse(str2.begin(), str2.end());

    if(str1.length() > str2.length())
        str1.swap(str2);

    bool carrie = 0;
    size_t j = str1.length();
    int rest = 0;

    for(size_t i = 0; i != str2.length(); ++i)
    {
        char a=str1[i];
        char b=str2[i];
        if (i<j)
        {
            rest = carrie + (int)a + ((int)b - 48);
        }
        else
        {
            rest = carrie + (int)b;
        }
        carrie = (rest - 48)/10;
        rest -= 10*carrie;
        res += (char)rest;
    }
    if (carrie == 1)
        res += '1';
    reverse(res.begin(), res.end());
    return Number(res);
}

Number Number::operator-(const Number &rhv) const
{
    std::string a = deZero(_num);
    std::string b = deZero(rhv._num);
    if(a == b)
        return Number("0");
    std::string s = a;
    for(int bi = b.length() - 1,si = s.length() - 1; si >= 0; si--,bi--)
    {
        if((s[si]-=(bi>=0?b[bi]-'0':0))<'0')
            s[si]+=10,s[si-1]--;
    }
    return Number(s.substr(s.find_first_not_of('0')));
}

bool Number::operator>(const Number &rhv) const
{
    if(_num.length() > rhv._num.length()) return true;
    if(_num.length() < rhv._num.length()) return false;
    long int i;
    for(i = 0; i < _num.length(); i++)
    {
        if(_num.at(i) > rhv._num.at(i)) return true;
        if(_num.at(i) < rhv._num.at(i)) return false;
    }
    return false;
}

bool Number::operator==(const Number &rhv) const
{
    if (_len != rhv._len)
        return false;
    return _num == rhv._num;
}

bool Number::operator!=(const Number &rhv) const { return !(_num == rhv._num); }

std::string Number::deZero(const std::string& str) const {
    std::string s = str;
    if (s.length() == 1) return s;
    int k = 0;
    for (int i = 0; i < s.length(); i++)
    {
        if (s[i] == '0')
            k++;
        else
            break;
    }
    if (k == s.length())
        s = "0";
    else
        s = s.substr(k);
    return s;
}


int Number::largerLength(Number& n1, Number& n2)
{
    int len1 = n1._len;
    int len2 = n2._len;
    if (len1 < len2)
    {
        addPrezero(n1._num, len2 - len1) ; // zero padding
        return len2;
    }
    else if (len1 > len2)
    {
        addPrezero(n2._num, len1 - len2) ; // zero padding
    }
    return len1; // If len1 >= len2
}

//Number Number::addLastzero(Number& s, unsigned int l)
//{
//    std::string s1 = s._num;
//    for (unsigned int i = 0; i < l; i++)
//        s1 += "0";
//    return Number(s1);
//}





