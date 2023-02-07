#pragma once

#include "vector.hpp"

const int PARTICLE_AMOUNT = 5000; // Needs calculating before running simulation
const double MAX_TIME = 5; // Correct
const double TIMESTEP = 0.01;
const double SIMULATION_SIZE_X = 0.315/2; // Correct
const double SIMULATION_SIZE_Y = 0.120/2; // Correct
const double SIMULATION_SIZE_Z = 0.230/2; // Correct

const Vector GRAVITY_ACCELRATION = Vector(0, -9.81, 0); // Correct (i think, or is there a better reference for this?)
const double PARTICLE_MASS = 0.01; // Needs calculating before running simulation
const double PARTICLE_RADIUS = 0.01; // Needs calculating before running simulation
const double DAMPENING_CONSTANT = 0.005; // Needs calculating before running simulation
