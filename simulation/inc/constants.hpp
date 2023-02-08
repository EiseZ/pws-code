#pragma once

#include <math.h>

#include "vector.hpp"

const double MAX_TIME = 5; // Correct = 5
const int PARTICLE_AMOUNT = 1000; // To change
const double TIMESTEP = 0.01; // To change
                              //
const double SIMULATION_SIZE_X = 0.315/2; // Correct
const double SIMULATION_SIZE_Y = 0.120/2; // Correct
const double SIMULATION_SIZE_Z = 0.230/2; // Correct

const Vector GRAVITY_ACCELRATION = Vector(0, -9.81, 0); // Correct (i think, or is there a better reference for this?)
const double WATER_HEIGTH = 0.021; // From video
const double PARTICLE_MASS = (2.0 / PARTICLE_AMOUNT); // 2 liters (kg)
const double PARTICLE_RADIUS = (cbrt((SIMULATION_SIZE_X * 2 * SIMULATION_SIZE_Y * 2 * SIMULATION_SIZE_Z * 2 * 0.74) / ((3/4) * 3.14159))) ; // Cube root of: volume of water * (constant of optimal sphere packing, source: https://www.nature.com/articles/425126c) / 3/4 * pi // Correct
const double DAMPENING_CONSTANT = 0.005; // Needs experimenting before running simulation

const double AVRG_PLANK_VELOCITY = 0.257;
