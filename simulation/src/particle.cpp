#include <math.h>
#include "particle.hpp"
#include "vector.hpp"

Particle::Particle(Vector pos, Vector vel, Vector acc) :
    pos(pos), vel(vel), acc(acc), force(Vector(0, 0, 0))
{}

double Particle::distance(Vector pos) const {
    double diffx = this->pos.x - pos.x;
    double diffy = this->pos.y - pos.y;
    double diffz = this->pos.z - pos.z;
    return sqrt(diffx * diffx + diffy * diffy + diffz * diffz);
}