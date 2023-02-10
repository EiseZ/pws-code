#pragma once

#include <string>
#include "constants.hpp"
#include "particle.hpp"

class Simulation {
private:
    Particle *particles[PARTICLE_AMOUNT];

public:
    Simulation();

    void calculateForces();
    void calculateAccelerations();
    void calculateVelocities();
    void calculatePositions(double currentTime,bool ignite);
    void printEnergy();

    std::string logState();
};
