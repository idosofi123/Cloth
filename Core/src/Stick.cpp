#include "ClothCore/Stick.h"
#include <math.h>

Stick::Stick(Point &pointA, Point &pointB, float length) : pointA(pointA), pointB(pointB), length(length) {

}

Stick::~Stick() {

}

void Stick::update(float deltaTime) {

    Vector pointsDiff = this->pointA.getPosition() - this->pointB.getPosition();
    float distance = sqrtf(pointsDiff.x * pointsDiff.x + pointsDiff.y * pointsDiff.y);

    Vector constraintOffset = pointsDiff * ((this->length - distance) / distance) * 0.5;

    this->pointA.setPosition(this->pointA.getPosition().x + constraintOffset.x, this->pointA.getPosition().y + constraintOffset.y);
    this->pointB.setPosition(this->pointB.getPosition().x - constraintOffset.x, this->pointB.getPosition().y - constraintOffset.y);
}