#pragma once
#include <memory>
#include <ClothCore/Point.h>
#include <ClothCore/Vector.h>
#include <ClothCore/Stick.h>

class Arrow {

private:

    std::unique_ptr<Point> startPoint;
    std::unique_ptr<Point> endPoint;
    Stick stick;
    Vector firingForce;
    double elapsedTime = 0.0;

    static constexpr double FIRING_FORCE_TIME = 0.01;

public:

    Arrow(Vector position, float length, Vector firingForce);
    Arrow(Arrow&&) = default;
    ~Arrow();

    void update(double deltaTime, double prevDeltaTime, const Vector &force);
    const Stick& getStick() const;

};