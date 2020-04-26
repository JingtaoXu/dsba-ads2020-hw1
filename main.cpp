#include <iostream>
#include <memory>
#include "Number.h"
#include "Multiplicator.h"
//#include <python.h>


/// task 4
double calcRunTime(std::shared_ptr<Multiplicator> method, const Number& n1, const Number& n2)
{
    double t = 0;
    clock_t startTime = clock();
    Number prod = (*method).mult(n1, n2);
    clock_t endTime = clock();
    t = (double)(endTime - startTime)/ CLOCKS_PER_SEC;

    std::cout << prod << "\n";

    return t;
}

/// task 6
std::vector<double> testResults(const Number& a, const Number& b)
{

    std::vector<double> time;
    double t1=0, t2=0, t3=0;

    for (int i = 0; i < 1; ++i) // 3 times
    {
        //        GradeSchool m1;
        std::shared_ptr<Multiplicator> m1 = std::make_shared<GradeSchool>();
        t1 += calcRunTime(m1, a, b);

//        DivideAndConquer m2;
        std::shared_ptr<Multiplicator> m2 = std::make_shared<DivideAndConquer>();
        t2 += calcRunTime(m2, a, b);

//        Karatsuba m3;
        std::shared_ptr<Multiplicator> m3 = std::make_shared<Karatsuba>();

        t3 += calcRunTime(m3, a, b);
    }
    double res1 = t1/3, res2 = t2/3, res3 = t3/3; // average RT
    time.push_back(res1);
    time.push_back(res2);
    time.push_back(res3);
    return time;
}

/// task 7 storing the result
void CSV_file(const std::vector<std::vector<double> >& v)
{
    // saving
    std::ofstream File;
    File.open("example.csv");

    for(int i = 0; i < v.size(); ++i)
    {
        File << i+1 << ','<< v[i][0] << ',' << v[i][1] << ',' << v[i][2] << "\n";

    }
    File.close();

    // loading
    std::ifstream file;
    file.open("example.csv");
    std::string line;
    while(getline(file, line,'\n'))
    {
        int start = 0;
        for(int i = 0; i < line.length(); ++i)
        {
            if(line[i] == ',')
            {
                std::cout << line.substr(start, i-start) << ' ';
                start = i + 1;
            }
        }
        std::cout << line.substr(start) << "\n";
    }
}

void test1()
{
    Number x("100");
    Number y("37");
    Number z;
    z = x - y;
//    cout << (x == y) << endl;
//    cout << x << endl;
    std::cout << (z.getStrNum());
}

void testBed()
{
    std::vector<std::vector<double> > resultVec;
    size_t k;
    std::cin >> k;

    for (size_t i = 1; i <= k; ++i)
    {
        std::string strX = Multiplicator::genRandom(i);
        std::string strY = Multiplicator::genRandom(i);

        //        cout << strX << "\t" << strY << endl;

        Number x(strX);
        Number y(strY);
        resultVec.push_back(testResults(x, y));
    }

    CSV_file(resultVec);
}

int main()
{
//    test1();
    testBed();
}