#ifndef PARTICLE_H
#define PARTICLE_H

#include <vector>
#include <iostream>

using Point = std::vector<double>;

struct Particle
{
    Point position;
    Point bestPosition;
    Point velocity;
    double fitness = { 0.0 };

    Particle(const Point::size_type n) :
        position(n, 0.0),
        bestPosition(n, 0.0),
        velocity(n, 0.0)
    {
    }
};

Point operator*(const double w, const Point& p);
Point operator+(const Point& p1, const Point& p2);
Point operator-(const Point& p1, const Point& p2);
std::ostream& operator<<(std::ostream& os, const Point& p);

double norm(const Point& p);

#endif
