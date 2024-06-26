#pragma once
#include <vector>
#include <memory>
#include "ClothCore/Point.h"
#include "ClothCore/Stick.h"
#include "ClothCore/Vector.h"

class Simulation {

private:

    std::vector<std::unique_ptr<Point>> points;
    std::vector<Stick> sticks;
    Vector currentForce{0 ,0};
    double prevDeltaTime = 0;

public:

    Simulation();
    ~Simulation();

    void addPoint(std::unique_ptr<Point> point);
    void addStick(Stick stick);
    void addForce(Vector force);
    void update(double deltaTime);
    const std::vector<std::unique_ptr<Point>>& getPoints() const;
    Point& getPoint(int index);
    std::vector<Stick>& getSticks();
};