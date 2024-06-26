#include "ClothCore/Simulation.h"

Simulation::Simulation() {

}

Simulation::~Simulation() {

}

void Simulation::addPoint(std::unique_ptr<Point> point) {
    this->points.push_back(std::move(point));
}

void Simulation::addStick(Stick stick) {
    this->sticks.push_back(stick);
}

void Simulation::addForce(Vector force) {
    this->currentForce += force;
}

void Simulation::update(double deltaTime) {

    for (auto &point : this->points) {
        point->update(deltaTime, this->prevDeltaTime, this->currentForce);
    }

    constexpr int CONSTRAINTS_UPDATE_ITERATIONS = 3;

    for (int i = 0; i < CONSTRAINTS_UPDATE_ITERATIONS; i++) {
        for (auto &stick : this->sticks) {
            stick.update(deltaTime);
        }
    }

    this->prevDeltaTime = deltaTime;
}

Point& Simulation::getPoint(int index) {
    return *(this->points[index]);
}

const std::vector<std::unique_ptr<Point>>& Simulation::getPoints() const {
    return this->points;
}

std::vector<Stick>& Simulation::getSticks() {
    return this->sticks;
}