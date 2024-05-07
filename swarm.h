#ifndef SWARM_H
#define SWARM_H

#include <iostream>
#include <vector>
#include <random>
#include <functional>

#include "particle.h"

class Swarm
{
public:
    Swarm(std::vector<Particle>::size_type swarmSize,
          std::vector<double>::size_type dim,
          double xMin, double xMax,
          double cognitive, double social,
          std::function<double (const Point&)> f);

    void nextGen();
    void print();
    Point bestPosition();

private:
    void initialize();

    double mMaxSpeed;
    double mInertiaWeight    = { 0.9 };
    double mInertiaStep      = { (0.9 - 0.4) / 10000 };
    double mCognitiveFactor;
    double mSocialFactor;

    std::vector<Particle> mParticles;
    Point mBestPosition;
    std::random_device mRD;
    std::mt19937 mRandomEngine;
    std::uniform_real_distribution<> mDistParticles;
    std::uniform_real_distribution<> mDist0_1;
    std::function<double (const Point& x)> mFitness;
};

#endif
