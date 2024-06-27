#include <iostream>
#include <raylib.h>
#include <ClothCore/Simulation.h>
#include <ClothCore/Collision.h>
#include <string>

int main() {
    
    constexpr int FPS = 120;
    constexpr int SCREEN_WIDTH = 1280;
    constexpr int SCREEN_HEIGHT = 720;
    constexpr int ROWS = 31;
    constexpr int COLS = 31;
    constexpr float SPACE = 8.f;
    constexpr float OFFSET_Y = 50.f;
    constexpr float OFFSET_X = (SCREEN_WIDTH - SPACE * (COLS - 1)) / 2;

    SetConfigFlags(FLAG_MSAA_4X_HINT); 
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Cloth");

    SetTargetFPS(FPS);

    Simulation simulation{SCREEN_HEIGHT - OFFSET_Y};
    simulation.addCloth(ROWS, COLS, SPACE, OFFSET_X, OFFSET_Y);
    simulation.addForce({ 40, 200 });
    simulation.addArrow({ 20, 500 }, 100, { 30000, -30000 });

    double previousTime = GetTime();

    while (!WindowShouldClose()) {

        // Handle Input
        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {

            Vector mousePos{ GetMousePosition().x, GetMousePosition().y };

            for (auto &stick : simulation.getSticks()) {
                const Vector& position = stick.getPointA().getPosition();
                float diffX = position.x - mousePos.x;
                float diffY = position.y - mousePos.y;
                if (diffX * diffX + diffY * diffY <= 25) {
                    stick.setIsActive(false);
                }
            }
        }

        // Update
        double currentTime = GetTime();
        simulation.update(currentTime - previousTime);
        previousTime = currentTime;

        // Render
        BeginDrawing();
        ClearBackground(BLACK);

        for (const auto &point : simulation.getPoints()) {
            if (point->getIsPinned()) {
                const Vector& position = point->getPosition();
                DrawCircle(position.x, position.y, 2, RED);
            }
        }

        for (const auto &stick : simulation.getSticks()) {

            if (!stick.getIsActive()) {
                continue;
            }

            const Vector& posA = stick.getPointA().getPosition();
            const Vector& posB = stick.getPointB().getPosition();
            DrawLine(posA.x, posA.y, posB.x, posB.y, WHITE);
        }

        for (const auto &arrow : simulation.getArrows()) {

            const Vector& posA = arrow.getStick().getPointA().getPosition();
            const Vector& posB = arrow.getStick().getPointB().getPosition();
            DrawLine(posA.x, posA.y, posB.x, posB.y, GOLD);
        }

        DrawText(std::to_string(1 / GetFrameTime()).c_str(), 30, 30, 24, WHITE);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}