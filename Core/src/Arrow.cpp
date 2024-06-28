#include "ClothCore/Arrow.h"

Arrow::Arrow(Vector position, float length, Vector firingForce) 
    : startPoint(std::make_unique<Point>(position - firingForce.normalize() * length)), 
      endPoint(std::make_unique<Point>(position)),
      stick(*this->startPoint, *this->endPoint, length),
      firingForce(firingForce) {

}

Arrow::~Arrow() {

}

void Arrow::update(double deltaTime, double prevDeltaTime, const Vector &force) {

    if (!this->fired) {
        this->fire(deltaTime);
        prevDeltaTime = deltaTime;
    }

    this->endPoint->update(deltaTime, prevDeltaTime, force);
    this->stick.update(deltaTime, 1.f);
}

const Stick &Arrow::getStick() const {
    return this->stick;
}

void Arrow::fire(double deltaTime) {
    this->endPoint->setInnerMomentum(this->firingForce * deltaTime);
    this->fired = true;
}
