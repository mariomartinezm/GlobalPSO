#include <cmath>
#include <algorithm>
#include <functional>

#include "particle.h"

Point operator*(const double w, const Point& p)
{
    Point res(p.size(), 0.0);

    std::transform(p.begin(), p.end(), res.begin(), [w](double pi)
                   {
                       return w * pi;
                   });

    return res;
}

Point operator+(const Point& p1, const Point& p2)
{
    Point res(p1.size(), 0.0);

    std::transform(p1.begin(), p1.end(), p2.begin(), res.begin(), std::plus<double>());

    return res;
}

Point operator-(const Point& p1, const Point& p2)
{
    Point res(p1.size(), 0.0);

    std::transform(p1.begin(), p1.end(), p2.begin(), res.begin(), std::minus<double>());

    return res;
}

std::ostream& operator<<(std::ostream& os, const Point& p)
{
    for(const auto& pi: p)
    {
        os << pi << " ";
    }

    os << "\n";

    return os;
}

double norm(const Point& p)
{
    double s = 0.0;

    for(const auto pi: p)
    {
        s += pi * pi;
    }

    return std::sqrt(s);
}
