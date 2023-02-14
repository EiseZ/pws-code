#include <string>
#include <iostream>
#include <algorithm>
#include "simulation.hpp"
#include "particle.hpp"
#include "constants.hpp"
#include <math.h>

int particlesTouching = 0;
bool preIgnition = false;
Simulation::Simulation() {
    Vector pos = Vector(SIMULATION_SIZE_X * -1, 0.0, 0);
    int currentRow = 0;
    int width = SIMULATION_SIZE_X * 2 / PARTICLE_RADIUS;
    int height = PARTICLE_AMOUNT/ width;
    for (int i = 0; i < PARTICLE_AMOUNT; i++) {
        pos.y = (WATER_HEIGTH / 2) - (height * PARTICLE_RADIUS * 0.86603/2) + (floor(i / width) * PARTICLE_RADIUS * 0.86603);
        pos.x = i % width * PARTICLE_RADIUS + ((int)floor(i/width) % 2 * PARTICLE_RADIUS) - SIMULATION_SIZE_X;
        if (pos.x < SIMULATION_SIZE_X) {
            pos.x += PARTICLE_RADIUS * 2;
        } else {
            pos.x = -1.0 * SIMULATION_SIZE_X + (currentRow % 2 * PARTICLE_RADIUS);
            pos.y = currentRow*0.86603* PARTICLE_RADIUS;
            currentRow++;
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
    Particle *newParticles[PARTICLE_AMOUNT];
    std::copy(particles, particles + PARTICLE_AMOUNT, newParticles);
    for (int i = 0; i < PARTICLE_AMOUNT; i++) {
        particles[i]->vel = particles[i]->vel.add(particles[i]->acc.multiply(TIMESTEP));
        //continue;
        for (int j = 0; j < PARTICLE_AMOUNT; j++) {
            if (i == j) {
                continue;
            }
            double distance = particles[i]->distance(particles[j]->pos);
            if (distance == 0) {
                particles[i]->pos.x += 0.000001;
            }
            if (distance < PARTICLE_RADIUS * 2) {
                //Link Source:https://ericleong.me/research/circle-circle/
                Particle* A = particles[i];
                Particle* B = particles[j];
                Vector vectorAtoB = B->pos.sub(A->pos);
                Vector normalizedAtoB = vectorAtoB.normalize();
                double p = (A->vel.dot(normalizedAtoB) - B->vel.dot(normalizedAtoB));
                newParticles[i]->vel = A->vel.sub(normalizedAtoB.multiply(p));
                newParticles[j]->vel = B->vel.add(normalizedAtoB.multiply(p));
            }
        }
    }
    std::copy(newParticles, newParticles + PARTICLE_AMOUNT, particles);
}

void Simulation::calculatePositions(double currentTime, bool ignite) {
    for (int i = 0; i < PARTICLE_AMOUNT; i++) {
        particles[i]->pos = particles[i]->pos.add(particles[i]->vel.multiply(TIMESTEP));

        double plankX = SIMULATION_SIZE_X;
        if (currentTime < 0.2) {
            plankX = SIMULATION_SIZE_X;
        } else if (currentTime < 0.5) {
            plankX = SIMULATION_SIZE_X - ((currentTime - 0.2) * AVRG_PLANK_VELOCITY);
        } else {
            plankX = SIMULATION_SIZE_X - (0.3 * AVRG_PLANK_VELOCITY);
        }

        if (particles[i]->pos.x > plankX) {
            if((currentTime > 0.5) && (currentTime < (0.5 + TIMESTEP))){
                if(ignite == false){
                    particlesTouching++;
                    preIgnition = true;
                }
                else{
                    preIgnition = false;
                    Particle* current = particles[i];
                    //current->vel.x = -1 * ( current->vel.len() + sqrt(2 * ENERGY_ADDED / particlesTouching / PARTICLE_MASS));
                    current->vel.x = -1 * ( current->vel.x + sqrt(2 * ENERGY_ADDED / particlesTouching / PARTICLE_MASS));
                    //current->vel.z = 0;
                    //current->vel.y = 0;
                    std::cout << current->vel.x << "\n";
                }
            }
            else{
                particles[i]->pos.x = plankX - (particles[i]->pos.x - plankX);
                particles[i]->vel.x = abs(particles[i]->vel.x) * -1;
            }
        } else if (particles[i]->pos.x < SIMULATION_SIZE_X * -1) {
            particles[i]->pos.x = SIMULATION_SIZE_X * -1 - (particles[i]->pos.x + SIMULATION_SIZE_X) ;
            particles[i]->vel.x = particles[i]->vel.x * -1.0;
        }
        if (particles[i]->pos.y < 0) {
            particles[i]->pos.y = 0.0 - particles[i]->pos.y;
            particles[i]->vel.y = particles[i]->vel.y * -1.0;
        }
        if (particles[i]->pos.z > SIMULATION_SIZE_Z) {
            particles[i]->pos.z = SIMULATION_SIZE_Z - particles[i]->pos.z + SIMULATION_SIZE_Z;
            particles[i]->vel.z = particles[i]->vel.z * -1.0;
        } else if (particles[i]->pos.z < SIMULATION_SIZE_Z * -1) {
            particles[i]->pos.z = SIMULATION_SIZE_Z * -1 - (particles[i]->pos.z + SIMULATION_SIZE_Z) ;
            particles[i]->vel.z = particles[i]->vel.z * -1.0;
        }
    }
    if(preIgnition){
        Simulation::calculatePositions(currentTime,true);
        std::cout << particlesTouching <<"\n";
    }
}
void Simulation::printEnergy(){
    double energy = 0.0;
    for (int i = 0; i < PARTICLE_AMOUNT; i++) {
        double x = particles[i]->vel.x;
        double y = particles[i]->vel.y;
        double z = particles[i]->vel.z;
        double len = sqrt(x*x + y*y + z*z);
        energy += 0.5 * len * len * PARTICLE_MASS;
        energy += particles[i]->pos.y * 9.81 * PARTICLE_MASS;
    }
    std::cout << "Energy: " << energy<< std::endl;
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

    double energy = 0.0;
    for (int i = 0; i < PARTICLE_AMOUNT; i++) {
        double x = particles[i]->vel.x;
        double y = particles[i]->vel.y;
        double z = particles[i]->vel.z;
        double len = sqrt(x*x + y*y + z*z);
        energy += 0.5 * len * len * PARTICLE_MASS;
        energy += particles[i]->pos.y * 9.81 * PARTICLE_MASS;
    }
    output.append(std::to_string(energy));

    output.append("\n");

    return output;
}
