#include "ClothCore/Simulation.h"
#include "ClothCore/Collision.h"
#include <algorithm>

Simulation::Simulation(float floorY, float floorX) : floorY(floorY), floorX(floorX) {
    
}

Simulation::~Simulation() {

}

void Simulation::addCloth(int rows, int columns, float space, float offsetX, float offsetY) {
    
    constexpr float CLOTH_THREAD_LIMIT = 25.f;

    for (int i = 0; i < rows; i++) {

        for (int j = 0; j < columns; j++) {

            this->addPoint(std::make_unique<Point>(Vector{ j * space + offsetX, i * space + offsetY }, 1, i == 0 && j % 10 == 0));

            if (i > 0) {
                this->addStick({ this->getPoint((i - 1) * columns + j), this->getPoint(i * columns + j), space, CLOTH_THREAD_LIMIT });
            }

            if (j > 0) {
                this->addStick({ this->getPoint(i * columns + j - 1), this->getPoint(i * columns + j), space, CLOTH_THREAD_LIMIT });
            }
        }   
    }
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

    constexpr int CONSTRAINTS_UPDATE_ITERATIONS = 5;

    for (auto &point : this->points) {
        point->update(deltaTime, this->prevDeltaTime, this->currentForce);
    }

    for (int i = 0; i < CONSTRAINTS_UPDATE_ITERATIONS; i++) {
        for (auto &stick : this->sticks) {
            stick.update(deltaTime);
        }
    }

    for (auto &arrow : this->arrows) {
        arrow.update(deltaTime, this->prevDeltaTime, this->currentForce);
    }

    this->resolveCollisions();
    this->constraintPoints();

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

void Simulation::addArrow(Vector position, float length, Vector firingForce) {
    this->arrows.push_back(Arrow{ position, length, firingForce });
}

const std::vector<Arrow>& Simulation::getArrows() {
    return this->arrows;  
}

void Simulation::constraintPoints() {
    for (auto &point : this->points) {
        const auto &position = point->getPosition();
        point->setPosition(std::clamp(position.x, 0.f, this->floorX), std::clamp(position.y, 0.f, this->floorY));
    }

    for (auto &arrow : this->arrows) {
        const auto &position = arrow.getStick().getPointB().getPosition();
        arrow.getStick().getPointB().setPosition(std::clamp(position.x, 0.f, this->floorX), std::clamp(position.y, 0.f, this->floorY));
    }
}

void Simulation::resolveCollisions() {

    for (auto &arrow : this->arrows) {

        for (auto &stick : this->sticks) {

            if (Collision::areLinesColliding(
                arrow.getStick().getPointA().getPosition(),
                arrow.getStick().getPointB().getPosition(),
                stick.getPointA().getPosition(),
                stick.getPointB().getPosition())) {

                stick.setIsActive(false);
            }
        }
    }
}