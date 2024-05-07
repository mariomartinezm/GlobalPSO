#include <algorithm>

#include "swarm.h"

Swarm::Swarm(std::vector<Particle>::size_type swarmSize,
             std::vector<double>::size_type dim,
             double xMin, double xMax,
             double cognitive, double social,
             std::function<double (const Point&)> f):
        mMaxSpeed(xMax - xMin),
        mCognitiveFactor(cognitive),
        mSocialFactor(social),
        mParticles(swarmSize, dim),
        mBestPosition(dim, 0.0),
        mRandomEngine(mRD()),
        mDistParticles(xMin, xMax),
        mDist0_1(0.0, 1.0),
        mFitness(f)
{
    initialize();
}

void Swarm::nextGen()
{
    for(auto& p: mParticles)
    {
        p.velocity = mInertiaWeight * p.velocity +
            mCognitiveFactor * mDist0_1(mRandomEngine) * (p.bestPosition - p.position) +
            mSocialFactor * mDist0_1(mRandomEngine) * (mBestPosition - p.position);

        double speed = norm(p.velocity);

        if(speed > mMaxSpeed)
        {
            p.velocity = mMaxSpeed * (1.0 / speed) * p.velocity;
        }

        // Update the particle's position
        p.position = p.position + p.velocity;

        double newFitness = mFitness(p.position);

        // If necessary update the particle's best position
        if(p.fitness > newFitness)
        {
            p.fitness = newFitness;
            p.bestPosition = p.position;
        }

        // If necessary update the swarm's best position
        if(mFitness(mBestPosition) > newFitness)
        {
            mBestPosition = p.position;
        }
    }

    mInertiaWeight -= mInertiaStep;
}

void Swarm::print()
{
    for(const auto& p: mParticles)
    {
        std::cout << "X: ";
        std::cout << p.position;

        std::cout << "V: ";
        std::cout << p.velocity;

        std::cout << "B: ";
        std::cout << p.bestPosition;

        std::cout <<"F: " << p.fitness << "\n\n";
    }

    std::cout << "G: ";
    std::cout << mBestPosition;
    std::cout <<"F: " << mFitness(mBestPosition) << "\n";
}

Point Swarm::bestPosition()
{
    return mBestPosition;
}

void Swarm::initialize()
{
    for(auto& p: mParticles)
    {
        // Randomize position
        for(auto& pi: p.position)
        {
            pi = mDistParticles(mRandomEngine);
        }

        // Randomize velocity
        for(auto& vi: p.velocity)
        {
            vi = mDistParticles(mRandomEngine);
        }

        // Set best position and fitness of each particle
        p.bestPosition = p.position;
        p.fitness = mFitness(p.position);
    }

    // Set the best position of the swarm
    auto res = std::min_element(mParticles.begin(), mParticles.end(),
                                [this](const Particle& p1, const Particle& p2)
                                {
                                    return p1.fitness < p2.fitness;
                                });

    mBestPosition = (*res).position;
}
