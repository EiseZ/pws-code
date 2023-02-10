#include <math.h>
#include <stdlib.h>
#include <iostream>
#include "vector.hpp"

Vector::Vector(double x, double y, double z) : x(x), y(y), z(z) {}

double Vector::len() const {
    double len = sqrt(x*x + y*y + z*z);
    if (len == 0) {
        std::cout << "[Error] Devide by zero!" << std::endl;
        exit(1);
    }
    return len;
}

Vector Vector::normalize() const {
    double len = this->len();
    Vector normalVec = Vector(this->x / len, this->y / len, this->z / len);
    return normalVec;
}

Vector Vector::multiply(double rhs) const {
    Vector product = Vector(this->x * rhs, this->y * rhs, this->z * rhs);
    return product;
}
Vector Vector::multiplyV(Vector *rhs) const {
    Vector product = Vector(this->x * rhs->x, this->y * rhs->y, this->z * rhs->z);
    return product;
}

Vector Vector::devide(double rhs) const {
    Vector product = Vector(this->x / rhs, this->y / rhs, this->z / rhs);
    return product;
}

Vector Vector::add(Vector vec) const {
    Vector sum = Vector(this->x + vec.x, this->y + vec.y, this->z + vec.z);
    return sum;
}

Vector Vector::sub(Vector vec) const {
    Vector diff = Vector(this->x - vec.x, this->y - vec.y, this->z - vec.z);
    return diff;
}

double Vector::dot(Vector vec) const {
    double res = (this->x * vec.x + this->y * vec.y + this->z * vec.z);
    return res;
}
