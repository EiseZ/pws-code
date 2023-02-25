import os

convertJ = [0.1,0.01,0.001,0.0005,0.00025]

for i in range(1,7):
    for j in range(1,6):
        os.system(f"cp /home/tim/Programming/pws-code/docker/template.hpp /home/tim/Programming/pws-code/docker/constants/{i}{j}.hpp")
        file = open(f"/home/tim/Programming/pws-code/docker/constants/{i}{j}.hpp","a")
        file.write(f"const int PARTICLE_AMOUNT = {i*1000};")
        file.write(f"const double TIMESTEP = {convertJ[j-1]};")
        file.write("""
const Vector GRAVITY_ACCELRATION = Vector(0, -9.81, 0); // Correct (i think, or is there a better reference for this?)
const double WATER_HEIGTH = 0.021; // From video
const double PARTICLE_MASS = (2.0 / PARTICLE_AMOUNT); // 2 liters (kg)
//const double PARTICLE_RADIUS = (cbrt((SIMULATION_SIZE_X * 2.0 * SIMULATION_SIZE_Y * 2.0 * SIMULATION_SIZE_Z * 2.0 * 0.74) / ((3.0/4.0) * 3.14159))) ; // Cube root of: volume of water * (constant of optimal sphere packing, source: https://www.nature.com/articles/425126c) / 3/4 * pi // Correct
const double AREAWATER = 2 * SIMULATION_SIZE_X * WATER_HEIGTH;
//const double PARTICLE_RADIUS = cbrt(0.555 * VOLUMEWATER / PARTICLE_AMOUNT / 3.14159);
const double PARTICLE_RADIUS = sqrt((AREAWATER * 0.9069)/(PARTICLE_AMOUNT*3.14159));
const double DAMPENING_CONSTANT = 0.0; // Needs experimenting before running simulation
const double ENERGY_ADDED = 0.07725375;

const double AVRG_PLANK_VELOCITY = 0.257;""")
        file.close()