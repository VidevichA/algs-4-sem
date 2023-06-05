#include <iostream>
#include <vector>
#include <cmath>
#include <string>

class Summator
{
public:
    Summator(std::vector<long long> a) : a(a)
    {
        k = std::floor(std::sqrt(a.size()));
        b = std::vector<long long>();
        for (long long i = 0; i < a.size(); i += k)
        {
            long long bsum = 0;
            for (long long j = i; j < i + k; ++j)
            {
                if (j >= a.size())
                {
                    bsum += 0;
                }
                else
                {
                    bsum += a[j];
                }
            }
            b.push_back(bsum);
        }
    }
    void Add(long long i, long long x)
    {
        a[i] += x;
        b[i / k] += x;
    }
    long long FindSum(long long l, long long r)
    {
        long long jl = l / k;
        long long jr = r / k;
        if (jl == jr)
        {
            long long sum = 0;
            for (long long i = l; i < r; ++i)
            {
                sum += a[i];
            }
            return sum;
        }
        long long s = 0;
        for (long long i = l; i < (jl + 1) * k; ++i)
        {
            s += a[i];
        }
        for (long long i = jl + 1; i < jr; ++i)
        {
            s += b[i];
        }
        for (long long i = jr * k; i < r; ++i)
        {
            s += a[i];
        }
        return s;
    }

private:
    std::vector<long long> a;
    std::vector<long long> b;
    long long k;
};

int main()
{
    long long size;
    std::cin >> size;
    std::vector<long long> e(size);
    for (long long i = 0; i < size; ++i)
    {
        long long temp;
        std::cin >> temp;
        e[i] = temp;
    }
    long long q;
    std::cin >> q;
    Summator s(e);
    for (long long i = 0; i < q; ++i)
    {
        std::string op;
        std::cin >> op;
        long long temp1;
        long long temp2;
        std::cin >> temp1;
        std::cin >> temp2;
        if (op == "Add")
        {
            s.Add(temp1, temp2);
        }
        else if (op == "FindSum")
        {
            std::cout << s.FindSum(temp1, temp2) << '\n';
        }
    }
    return 0;
}