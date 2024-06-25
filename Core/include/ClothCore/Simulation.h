#pragma once
#include <vector>
#include "ClothCore/Point.h"
#include "ClothCore/Stick.h"
#include "ClothCore/Vector.h"

class Simulation {

private:

    std::vector<Point> points;
    std::vector<Stick> sticks;
    Vector currentForce{0 ,0};
    float prevDeltaTime = 0;

public:

    Simulation();
    ~Simulation();

    void addPoint(Point point);
    void addStick(Stick stick);
    void addForce(Vector force);
    void update(float deltaTime);
    const std::vector<Point>& getPoints() const;
    const std::vector<Stick>& getSticks() const;
};