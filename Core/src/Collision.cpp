#include "ClothCore/Collision.h"

bool Collision::areLinesColliding(Vector startA, Vector endA, Vector startB, Vector endB) {

    const float 
        x1 = startA.x, y1 = startA.y,
        x2 = endA.x,   y2 = endA.y,
        x3 = startB.x, y3 = startB.y,
        x4 = endB.x,   y4 = endB.y;

    float denominator = (y4 - y3) * (x2 - x1) - (x4 - x3) * (y2 - y1);
    float u1 = (x4 - x3) * (y1 - y3) - (y4 - y3) * (x1 - x3);
    float u2 = (x2 - x1) * (y1 - y3) - (y2 - y1) * (x1 - x3);

    if (denominator == 0.f) {
        return u1 == 0.f && u2 == 0.f;
    }

    u1 /= denominator;
    u2 /= denominator;

    return u1 >= 0 && u1 <= 1 && u2 >= 0 && u2 <= 1;
}