#include <string>
#include <iostream>
#include "simulation.hpp"
#include "particle.hpp"
#include "constants.hpp"

Simulation::Simulation() {
    Vector pos = Vector(SIMULATION_SIZE_X * -1, SIMULATION_SIZE_Y, 0);
    for (int i = 0; i < PARTICLE_AMOUNT; i++) {
        if (pos.x < SIMULATION_SIZE_X) {
            pos.x += PARTICLE_RADIUS * 2.1;
        } else {
            pos.x -= (SIMULATION_SIZE_X * 2) - 0.0002;
            pos.y += PARTICLE_RADIUS * 2.1;
        }
        if (pos.y >= SIMULATION_SIZE_Y) {
            pos.y = SIMULATION_SIZE_Y * -1 + 0.0002;
        }

        particles[i] = new Particle(Vector(pos.x, pos.y, pos.z), Vector(0, 0, 0), Vector(0, 0, 0));
    }

}

void Simulation::calculateForces() {
    for (int i = 0; i < PARTICLE_AMOUNT; i++) {
        Vector force = Vector(0, 0, 0);
        force = force.add(GRAVITY_ACCELRATION.multiply(PARTICLE_MASS));
        //force = force.add(particles[i]->vel.multiply(DAMPENING_CONSTANT * -1));
        particles[i]->force = force;
    }
}

void Simulation::calculateAccelerations() {
    for (int i = 0; i < PARTICLE_AMOUNT; i++) {
        particles[i]->acc = particles[i]->force.devide(PARTICLE_MASS);
    }
}

void Simulation::calculateVelocities() {
    for (int i = 0; i < PARTICLE_AMOUNT; i++) {
        particles[i]->vel = particles[i]->vel.add(particles[i]->acc.multiply(TIMESTEP));

        for (int j = 0; j < PARTICLE_AMOUNT; j++) {
            if (i == j) {
                continue;
            }
            double distance = particles[i]->distance(particles[j]->pos);
            if (distance == 0) {
                particles[i]->pos.x += 0.000001;
            }
            if (distance < PARTICLE_RADIUS * 2) {
                Vector vectorItoJ = particles[j]->pos.sub(particles[i]->pos);
                Vector normalizedItoJ = vectorItoJ.normalize();
                Vector relativeVelocity = particles[i]->vel.sub(particles[j]->vel);
                Vector normalVelocity = normalizedItoJ.multiply(relativeVelocity.dot(normalizedItoJ));
                if (distance / 2 < PARTICLE_RADIUS) {
                    Vector pointOfCollision = vectorItoJ.multiply(0.5);
                    double ratioOfRadius = distance / PARTICLE_RADIUS * 2;
                    particles[i]->pos = particles[i]->pos.add(pointOfCollision).add(pointOfCollision.multiply(-1 * ratioOfRadius));
                }
                particles[i]->vel = particles[i]->vel.sub(normalVelocity).multiply(1 - DAMPENING_CONSTANT);
                particles[j]->vel = particles[j]->vel.add(normalVelocity).multiply(1 - DAMPENING_CONSTANT);
            }
        }
    }
}

void Simulation::calculatePositions(double currentTime) {
    for (int i = 0; i < PARTICLE_AMOUNT; i++) {
        particles[i]->pos = particles[i]->pos.add(particles[i]->vel.multiply(TIMESTEP));

        double plankX;
        if (currentTime < 0.5) {
            plankX = SIMULATION_SIZE_X - (currentTime * AVRG_PLANK_VELOCITY);
        } else {
            plankX = SIMULATION_SIZE_X - (0.5 * AVRG_PLANK_VELOCITY);
        }

        if (particles[i]->pos.x > plankX) {
            particles[i]->pos.x = plankX;
            particles[i]->vel.x = abs(particles[i]->vel.x) * -1 - AVRG_PLANK_VELOCITY;
        } else if (particles[i]->pos.x < SIMULATION_SIZE_X * -1) {
            particles[i]->pos.x = SIMULATION_SIZE_X * -1;
            particles[i]->vel.x = particles[i]->vel.x * -0.5;
        }
        if (particles[i]->pos.y > SIMULATION_SIZE_Y) {
            particles[i]->pos.y = SIMULATION_SIZE_Y;
            particles[i]->vel.y = particles[i]->vel.y * -0.5;
        } else if (particles[i]->pos.y < SIMULATION_SIZE_Y * -1) {
            particles[i]->pos.y = SIMULATION_SIZE_Y * -1;
            particles[i]->vel.y = particles[i]->vel.y * -0.5;
        }
        if (particles[i]->pos.z > SIMULATION_SIZE_Z) {
            particles[i]->pos.z = SIMULATION_SIZE_Z;
            particles[i]->vel.z = particles[i]->vel.z * -0.5;
        } else if (particles[i]->pos.z < SIMULATION_SIZE_Z * -1) {
            particles[i]->pos.z = SIMULATION_SIZE_Z * -1;
            particles[i]->vel.z = particles[i]->vel.z * -0.5;
        }
    }
}

std::string Simulation::logState() {
    std::string output;
    for (int i = 0; i < PARTICLE_AMOUNT; i++) {
        output.append(std::to_string(particles[i]->pos.x));
        output.append(",");
        output.append(std::to_string(particles[i]->pos.y));
        output.append(",");
        output.append(std::to_string(particles[i]->pos.z));
        output.append(",");
    }

    output.pop_back();
    output.append("\n");

    return output;
}
