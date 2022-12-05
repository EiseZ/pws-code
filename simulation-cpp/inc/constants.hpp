#pragma once

#include "vector.hpp"

const int PARTICLE_AMOUNT = 5000;
const double MAX_TIME = 5;
const double TIMESTEP = 0.01;
const double SIMULATION_SIZE = 1;

const Vector GRAVITY_ACCELRATION = Vector(0, -9.81, 0);
const double PARTICLE_MASS = 0.01;
const double PARTICLE_RADIUS = 0.01;
const double DAMPENING_CONSTANT = 0.005;
