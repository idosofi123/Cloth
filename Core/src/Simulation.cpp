#include "ClothCore/Simulation.h"

Simulation::Simulation() {

}

Simulation::~Simulation() {

}

void Simulation::addPoint(Point point) {
    this->points.push_back(point);
}

void Simulation::addStick(Stick stick) {
    this->sticks.push_back(stick);
}

void Simulation::addForce(Vector force) {
    this->currentForce += force;
}

void Simulation::update(float deltaTime) {

    for (auto &point : this->points) {
        point.update(deltaTime, this->prevDeltaTime, this->currentForce);
    }

    this->prevDeltaTime = deltaTime;
}

const std::vector<Point>& Simulation::getPoints() const {
    return this->points;
}

const std::vector<Stick>& Simulation::getSticks() const {
    return this->sticks;
}