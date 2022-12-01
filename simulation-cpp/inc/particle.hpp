#pragma once

#include "vector.hpp"

class Particle {
public:
    Vector pos;
    Vector vel;
    Vector acc;
    Vector force;

    Particle(Vector pos, Vector vel, Vector acc);

    double distance(Vector pos) const;
};