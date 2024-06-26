#include "ClothCore/Stick.h"
#include <math.h>

Stick::Stick(Point &pointA, Point &pointB, float length) : pointA(pointA), pointB(pointB), length(length) {

}

Stick::~Stick() {

}

const Point& Stick::getPointA() const {
    return this->pointA;
}

const Point& Stick::getPointB() const {
    return this->pointB;
}

void Stick::update(double deltaTime) {

    if (!this->isActive) {
        return;
    }

    Vector pointsDiff = this->pointA.getPosition() - this->pointB.getPosition();

    float distance = sqrtf(pointsDiff.x * pointsDiff.x + pointsDiff.y * pointsDiff.y);

    Vector constraintOffset = pointsDiff * ((this->length - distance) / distance) * 0.5;

    this->pointA.setPosition(this->pointA.getPosition().x + constraintOffset.x, this->pointA.getPosition().y + constraintOffset.y);
    this->pointB.setPosition(this->pointB.getPosition().x - constraintOffset.x, this->pointB.getPosition().y - constraintOffset.y);
}

void Stick::setIsActive(bool isActive) {
    this->isActive = isActive;
}

bool Stick::getIsActive() const {
    return this->isActive;
}