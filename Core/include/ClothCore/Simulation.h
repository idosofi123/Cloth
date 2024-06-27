#pragma once
#include <vector>
#include <memory>
#include "ClothCore/Point.h"
#include "ClothCore/Stick.h"
#include "ClothCore/Vector.h"
#include "ClothCore/Arrow.h"

class Simulation {

private:

    std::vector<std::unique_ptr<Point>> points;
    std::vector<Stick> sticks;
    std::vector<Arrow> arrows;
    Vector currentForce{0 ,0};
    double prevDeltaTime = 0;
    float floorY;
    float floorX;

    void constraintPoints();
    void resolveCollisions();

public:

    Simulation(float floorY, float floorX);
    ~Simulation();

    void addPoint(std::unique_ptr<Point> point);
    void addStick(Stick stick);
    void addCloth(int rows, int columns, float space, float offsetX, float offsetY);
    void addForce(Vector force);
    void update(double deltaTime);
    const std::vector<std::unique_ptr<Point>>& getPoints() const;
    Point& getPoint(int index);
    std::vector<Stick>& getSticks();
    void addArrow(Vector position, float length, Vector firingForce);
    const std::vector<Arrow>& getArrows();
};