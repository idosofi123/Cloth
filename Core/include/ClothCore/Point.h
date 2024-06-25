#pragma once
#include "ClothCore/Vector.h"

class Point {

private:

    Vector currentPosition;
    Vector prevPosition;
    float prevDeltaTime = 0;
    float mass;
    bool isPinned;

public:

    Point(float x, float y, float mass = 1, bool isPinned = false);
    ~Point();

    const Vector& getPosition() const;
    void setPosition(float x, float y);
    void setIsPinned(bool isPinned);
    void update(float deltaTime, float prevDeltaTime, const Vector& force);
};