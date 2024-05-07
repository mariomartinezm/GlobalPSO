#include <iostream>
#include <cmath>
#include <numeric>

#include "swarm.h"

constexpr double PI = 3.1415926535;

double f1(const Point& x)
{
    double s = std::accumulate(x.begin(), x.end(), 0.0, [](const double& a, const double& b)
                               {
                                    return std::abs(a) + std::abs(b);
                               });

    double p = std::accumulate(x.begin(), x.end(), 1.0, [](const double& a, const double& b)
                               {
                                    return std::abs(a) * std::abs(b);
                               });

    return s + p;
}

double sphere(const Point& x)
{
    double s = 0.0;
    for(const auto& xi: x)
    {
        s += (xi * xi);
    }
    return s;
}

double rastrigin(const Point& x)
{
    constexpr int a = 10;
    double s = a * x.size();

    for(const auto& xi: x)
    {
        s += (xi * xi) - a * cos(2 * PI * xi);
    }

    return s;
}

double goldsteinPrice(const Point& p)
{
    auto x = p[0];
    auto y = p[1];

    return (1  + (x + y + 1) * (x + y + 1) *
           (19 - 14 * x + 3 * x * x - 14 * y + 6 * x * y + 3 * y * y)) *
           (30 + (2 * x - 3 * y) * (2 * x - 3 * y) *
           (18 - 32 * x + 12 * x * x + 48 * y - 36 * x * y + 27 * y * y));
}

int main()
{
    auto f = goldsteinPrice;

    Swarm s(40, 2, -2.0, 2.0, 2.0, 2.0, f);

    for(int i = 0; i < 10000; i++)
    {
        s.nextGen();
    }

    std::cout << "Best position: " << s.bestPosition();
    std::cout << "Best fitness: " << f(s.bestPosition()) << "\n";

    return 0;
}
