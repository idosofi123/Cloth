#pragma once
#include <math.h>

struct Vector {

    float x;
    float y;
    
    Vector operator+(const Vector &other) {
        return { this->x + other.x, this->y + other.y };
    }

    Vector operator-(const Vector &other) const {
        return { this->x - other.x, this->y - other.y };
    }

    Vector operator-(float other) const {
        return { this->x - other, this->y - other };
    }

    Vector operator+(float other) const {
        return { this->x + other, this->y + other };
    }

    Vector& operator+=(const Vector &other) {
        this->x += other.x;
        this->y += other.y;
        return *this;
    }

    Vector operator*(float scalar) {
        return { this->x * scalar, this->y * scalar };
    }

    Vector normalize() {
        return *this * (1.f / sqrtf(this->x * this->x + this->y * this->y));
    }
};

