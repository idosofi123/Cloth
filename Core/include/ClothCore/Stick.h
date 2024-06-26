#pragma once
#include "ClothCore/Point.h"

class Stick {

private:
    Point& pointA;    
    Point& pointB;
    float length;
    bool isActive = true;

public:

    Stick(Point& pointA, Point& pointB, float length);
    ~Stick();

    void update(double deltaTime);
    const Point& getPointA() const;
    const Point& getPointB() const;
    void setIsActive(bool isActive);
    bool getIsActive() const;

};