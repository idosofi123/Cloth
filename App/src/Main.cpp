#include <iostream>
#include <raylib.h>
#include <ClothCore/Simulation.h>
#include <string>

int main() {
    
    constexpr int FPS = 60;

    InitWindow(1280, 720, "Cloth");

    SetTargetFPS(FPS);

    Simulation simulation;
    simulation.addForce({ 70, 10 });
    simulation.addPoint({ 30, 30 });
    
    // double previousTime = GetTime();

    while (!WindowShouldClose()) {

        simulation.update(GetFrameTime());

        BeginDrawing();
        ClearBackground(BLACK);

        for (const auto &point : simulation.getPoints()) {
            const Vector& position = point.getPosition();
            DrawRectangle(position.x, position.y, 30, 30, WHITE);
        }

        for (const auto &stick : simulation.getSticks()) {

        }

        EndDrawing();
    }

    CloseWindow();

    return 0;
}