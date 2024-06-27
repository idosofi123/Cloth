#include "ClothCore/Point.h"

Point::Point(Vector position, float mass, bool isPinned) : currentPosition(position), prevPosition(position), mass(mass), isPinned(isPinned) {
    
}

Point::~Point() {

}

const Vector& Point::getPosition() const {
    return this->currentPosition;
}

void Point::update(double deltaTime, double prevDeltaTime, const Vector &force) {

    if (isPinned) return;

    Vector acceleration{ force.x / mass, force.y / mass }, currentPositionCopy = this->currentPosition;

    if (prevDeltaTime == 0.f) {
        prevDeltaTime = deltaTime == 0 ? 1 : deltaTime;
    }

    this->currentPosition.x += (this->currentPosition.x - this->prevPosition.x) * deltaTime / prevDeltaTime + acceleration.x * deltaTime * (deltaTime + prevDeltaTime) / 2;
    this->currentPosition.y += (this->currentPosition.y - this->prevPosition.y) * deltaTime / prevDeltaTime + acceleration.y * deltaTime * (deltaTime + prevDeltaTime) / 2;

    this->prevPosition = currentPositionCopy;
}

void Point::setInnerMomentum(Vector force) {
    this->prevPosition = this->currentPosition - force;
}

void Point::setIsPinned(bool isPinned) {
    this->isPinned = isPinned;
}

void Point::setPosition(float x, float y) {

    if (isPinned) return;

    this->currentPosition.x = x;
    this->currentPosition.y = y;
}