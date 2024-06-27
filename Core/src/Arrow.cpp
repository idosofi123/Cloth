#include "ClothCore/Arrow.h"

Arrow::Arrow(Vector position, float length, Vector firingForce) 
    : startPoint(std::make_unique<Point>(position - firingForce.normalize() * (length / 2))), 
      endPoint(std::make_unique<Point>(position + firingForce.normalize() * (length / 2))),
      stick(*this->startPoint, *this->endPoint, length),
      firingForce(firingForce) {

}

Arrow::~Arrow() {

}

void Arrow::update(double deltaTime, double prevDeltaTime, const Vector &force) {

    double firingForceAppliedTime = std::min(std::max(FIRING_FORCE_TIME - this->elapsedTime, 0.0), deltaTime);

    if (firingForceAppliedTime > 0.0) {

        Vector enhancedForce = this->firingForce + force;

        this->endPoint->update(firingForceAppliedTime, prevDeltaTime, enhancedForce);    

        deltaTime -= firingForceAppliedTime;
        prevDeltaTime = firingForceAppliedTime;
    }

    if (deltaTime > 0.0) {
        this->endPoint->update(deltaTime, prevDeltaTime, force);
    }

    this->stick.update(deltaTime, 1.f);
    
    this->elapsedTime += deltaTime;
}

const Stick &Arrow::getStick() const {
    return this->stick;
}
