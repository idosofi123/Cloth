#include <iostream>
#include <raylib.h>
#include <ClothCore/Simulation.h>
#include <string>

int main() {
    
    constexpr int FPS = 60;
    constexpr float SPACE = 8.f;
    constexpr float OFFSET = 100.f;
    constexpr int ROWS = 49;
    constexpr int COLS = 49;

    SetConfigFlags(FLAG_MSAA_4X_HINT); 
    InitWindow(1280, 720, "Cloth");

    SetTargetFPS(FPS);

    Simulation simulation;
    simulation.addForce({ 20, 150 });

    for (int i = 0; i < ROWS; i++) {

        for (int j = 0; j < COLS; j++) {

            simulation.addPoint(std::make_unique<Point>(j * SPACE + OFFSET, i * SPACE + OFFSET, 1, i == 0 && j % 3 == 0));

            if (i > 0) {
                simulation.addStick({ simulation.getPoint((i - 1) * COLS + j), simulation.getPoint(i * COLS + j), SPACE });
            }

            if (j > 0) {
                simulation.addStick({ simulation.getPoint(i * COLS + j - 1), simulation.getPoint(i * COLS + j), SPACE });
            }
        }   
    }

    double previousTime = GetTime();

    while (!WindowShouldClose()) {

        // Handle Input
        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {

            Vector2 mousePos = GetMousePosition();

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
                DrawCircle(position.x, position.y, 1, point->getIsPinned() ? RED : WHITE);
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

        EndDrawing();
    }

    CloseWindow();

    return 0;
}