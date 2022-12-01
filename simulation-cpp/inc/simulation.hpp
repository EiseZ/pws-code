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
    void calculatePositions();

    std::string logState();
};