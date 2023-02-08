#include <iostream>
#include <fstream>
#include "simulation.hpp"
#include "constants.hpp"

int main() {
    // Create file
    std::ofstream filestream;
    filestream.open("output.csv");

    std::cout << PARTICLE_MASS << "\n";

    Simulation simulation;
    double currentTime = 0;
    while (currentTime  <= MAX_TIME) {
        simulation.calculateForces();
        simulation.calculateAccelerations();
        simulation.calculateVelocities();
        simulation.calculatePositions(currentTime);
        filestream << simulation.logState();

        std::cout << "Current time: " << currentTime << std::endl;
        currentTime += TIMESTEP;
    }

    filestream.close();
    return 0;
}
