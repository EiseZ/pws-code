#include <string>
#include <iostream>
#include "simulation.hpp"
#include "particle.hpp"
#include "constants.hpp"

Simulation::Simulation() {
    Vector pos = Vector(0, 0, 0);
    particles[0] = new Particle(Vector(0, 1, 0), Vector(0.2, 0, 0), Vector(0, 0, 0));
    for (int i = 1; i < PARTICLE_AMOUNT; i++) {
        particles[i] = new Particle(pos, Vector(0, 0, 0), Vector(0, 0, 0));
        pos.x += 0.1;
    }

}

void Simulation::calculateForces() {
    for (int i = 0; i < PARTICLE_AMOUNT; i++) {
        Vector force = Vector(0, 0, 0);
        force = force.add(GRAVITY_ACCELRATION.multiply(PARTICLE_MASS));
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
            std::cout << std::to_string(distance) << std::endl;
            if (distance < PARTICLE_RADIUS * 2) {
                Vector vectorItoJ = particles[j]->pos.sub(particles[i]->pos);                        
                Vector normalizedItoJ = vectorItoJ.normalize();
                Vector relativeVelocity = particles[i]->vel.sub(particles[j]->vel);
                Vector normalVelocity = normalizedItoJ.multiply(relativeVelocity.dot(normalizedItoJ));
                particles[i]->vel = particles[i]->vel.sub(normalVelocity);
                particles[j]->vel = particles[j]->vel.add(normalVelocity);
            }
        }
    }
}

void Simulation::calculatePositions() {
    for (int i = 0; i < PARTICLE_AMOUNT; i++) {
        particles[i]->pos = particles[i]->pos.add(particles[i]->vel.multiply(TIMESTEP));
        
        if (particles[i]->pos.x > SIMULATION_SIZE) {
            particles[i]->pos.x = SIMULATION_SIZE;
            particles[i]->vel.x = particles[i]->vel.x * -1;
        } else if (particles[i]->pos.x < SIMULATION_SIZE * -1) {
            particles[i]->pos.x = SIMULATION_SIZE * -1;
            particles[i]->vel.x = particles[i]->vel.x * -1;
        }
        if (particles[i]->pos.y > SIMULATION_SIZE) {
            particles[i]->pos.y = SIMULATION_SIZE;
            particles[i]->vel.y = particles[i]->vel.y * -1;
        } else if (particles[i]->pos.y < SIMULATION_SIZE * -1) {
            particles[i]->pos.y = SIMULATION_SIZE * -1;
            particles[i]->vel.y = particles[i]->vel.y * -1;
        }
        if (particles[i]->pos.z > SIMULATION_SIZE) {
            particles[i]->pos.z = SIMULATION_SIZE;
            particles[i]->vel.z = particles[i]->vel.z * -1;
        } else if (particles[i]->pos.z < SIMULATION_SIZE * -1) {
            particles[i]->pos.z = SIMULATION_SIZE * -1;
            particles[i]->vel.z = particles[i]->vel.z * -1;
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