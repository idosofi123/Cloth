#include "ClothCore/Stick.h"
#include <math.h>

Stick::Stick(Point &pointA, Point &pointB, float length, float limit) : pointA(pointA), pointB(pointB), length(length), limit(limit) {

}

Stick::~Stick() {

}

Point& Stick::getPointA() const {
    return this->pointA;
}

Point& Stick::getPointB() const {
    return this->pointB;
}

void Stick::update(double deltaTime, float pointAFactor) {

    if (!this->isActive) {
        return;
    }

    Vector pointsDiff = this->pointA.getPosition() - this->pointB.getPosition();

    float distance = sqrtf(pointsDiff.x * pointsDiff.x + pointsDiff.y * pointsDiff.y);

    if (this->limit > 0.f && distance > this->limit && !this->pointA.getIsPinned() && !this->pointB.getIsPinned()) {
        this->setIsActive(false);
        return;
    }

    Vector constraintOffset = pointsDiff * ((this->length - distance) / distance);

    Vector constraintOffsetA = constraintOffset * pointAFactor;
    Vector constraintOffsetB = constraintOffset * (1 - pointAFactor);

    this->pointA.setPosition(this->pointA.getPosition().x + constraintOffsetA.x, this->pointA.getPosition().y + constraintOffsetA.y);
    this->pointB.setPosition(this->pointB.getPosition().x - constraintOffsetB.x, this->pointB.getPosition().y - constraintOffsetB.y);
}

void Stick::setIsActive(bool isActive) {
    this->isActive = isActive;
}

bool Stick::getIsActive() const {
    return this->isActive;
}