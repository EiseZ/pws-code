#pragma once

class Vector {
public:
    double x;
    double y;
    double z;

    Vector(double x, double y, double z);

    double len() const;
    Vector normalize() const;

    Vector multiply(double rhs) const;
    Vector devide(double rhs) const;
    Vector add(Vector vec) const;
    Vector sub(Vector vec) const;
    double dot(Vector vec) const;
};