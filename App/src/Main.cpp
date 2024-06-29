#include <iostream>
#include <raylib.h>
#include <ClothCore/Simulation.h>
#include <ClothCore/Collision.h>
#include <string>
#include <format>

void drawArrow(const Arrow &arrow) {
    const Vector& posA = arrow.getStick().getPointA().getPosition();
    const Vector& posB = arrow.getStick().getPointB().getPosition();
    DrawLineEx({posA.x, posA.y}, {posB.x, posB.y}, 3.f, { 177 - 50, 255 - 50, 254 - 50, 255 });
}

int main() {
    
    constexpr int FPS = 120;
    constexpr int SCREEN_WIDTH = 1920;
    constexpr int SCREEN_HEIGHT = 1080;
    constexpr int ROWS = 80;
    constexpr int COLS = 91;
    constexpr float SPACE = 7.f;
    constexpr float OFFSET_Y = 50.f;
    constexpr float OFFSET_X = (SCREEN_WIDTH - SPACE * (COLS - 1)) / 2;
    constexpr float ARROW_LENGTH = 75.f;
    constexpr float ARROW_FORCE_SCALAR = 5.f;
    constexpr Vector ENVIRONMENT_FORCE{ 50, 200 };

    SetConfigFlags(FLAG_MSAA_4X_HINT); 
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Cloth");

    SetTargetFPS(FPS);
    SetWindowState(FLAG_VSYNC_HINT);

    Simulation simulation{SCREEN_HEIGHT - OFFSET_Y, SCREEN_WIDTH};
    simulation.addCloth(ROWS, COLS, SPACE, OFFSET_X, OFFSET_Y);
    simulation.addForce(ENVIRONMENT_FORCE);

    double previousTime = GetTime();

    Shader bloomShader = LoadShader(nullptr, TextFormat("./assets/shaders/bloom.fs", 330));
    RenderTexture2D target = LoadRenderTexture(SCREEN_WIDTH, SCREEN_HEIGHT);

    Vector2 arrowEndpoint;
    bool isInitiatingArrow = false;

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

        if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)) {

            arrowEndpoint = GetMousePosition();
            isInitiatingArrow = true;
        }

        if (IsMouseButtonReleased(MOUSE_RIGHT_BUTTON)) {

            Vector mousePos{ GetMousePosition().x, GetMousePosition().y };
            Vector arrowPos{ arrowEndpoint.x, arrowEndpoint.y };

            simulation.addArrow({ arrowEndpoint.x, arrowEndpoint.y }, ARROW_LENGTH, (arrowPos - mousePos) * ARROW_FORCE_SCALAR);

            isInitiatingArrow = false;
        }

        // Update
        double currentTime = GetTime();
        double deltaTime = currentTime - previousTime;
        simulation.update(deltaTime);

        previousTime = currentTime;

        // Render
        BeginTextureMode(target);

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
                drawArrow(arrow);
            }

            if (isInitiatingArrow) {
                DrawLineEx(GetMousePosition(), arrowEndpoint, 2.f, PINK);
            }

        EndTextureMode();

        BeginDrawing();

            ClearBackground(BLACK);

            BeginShaderMode(bloomShader);
                DrawTextureRec(target.texture, Rectangle{ 0, 0, (float)target.texture.width, (float)-target.texture.height }, Vector2{ 0, 0 }, WHITE);
            EndShaderMode();

            DrawText(("FPS: " + std::to_string(static_cast<int>(std::round(1 / GetFrameTime())))).c_str(), 30, 30, 24, WHITE);
            DrawText((std::format("Environmental Force: ({}, {})", ENVIRONMENT_FORCE.x, ENVIRONMENT_FORCE.y)).c_str(), 30, 60, 24, WHITE);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}