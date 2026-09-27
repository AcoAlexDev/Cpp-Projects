#include <iostream>
#include <array>
#include <vector>
#include <string>
#include <algorithm>
#include <raylib.h>
#include <cmath>

class DrawALine
{
public:
    double distance(double x1, double y1, double x2, double y2)
    {
        return std::hypot(x2 - x1, y2 - y1);
    }

    double calculateAccuracy()
    {
        finished = true;
        if (positions.size() < 2)
        {
            error = "Invalid shape";
            return 0.0;
        }

        const Vector2 start = positions.front();
        const Vector2 end = positions.back();
        const double lineLength = distance(start.x, start.y, end.x, end.y);
        if (lineLength < 220.0)
        {
            error = "Line is too short";
            return 0.0;
        }

        double offset = 0.0;
        const double dx = end.x - start.x;
        const double dy = end.y - start.y;
        for (const Vector2& position : positions)
        {
            const double pointDx = position.x - start.x;
            const double pointDy = position.y - start.y;
            offset += std::abs(dx * pointDy - dy * pointDx) / lineLength;
        }

        double avgOffset = offset / static_cast<double>(positions.size());
        double maxAcceptableOffset = 20.0; // pixels — tune to taste; smaller = stricter
        double accuracyScore = 100.0 * (1.0 - std::min(avgOffset / maxAcceptableOffset, 1.0));
        return std::max(0.0, accuracyScore);
    };

    void main()
    {

        InitWindow(width, height, "Draw A Line");
        SetTargetFPS(60);
        while(!WindowShouldClose())
        {
            if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                positions.clear();
                finished = false;
                error = "";
            }
            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) positions.push_back(GetMousePosition());
            else if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
            {
                accuracy = calculateAccuracy();
            }

            BeginDrawing();

            ClearBackground(BLACK);

            if (!error.empty())
            {
                DrawText(error.c_str(), width/2, height/2, 20, RED);
            }
            else if (positions.empty())
            {
                DrawText("Draw A Line", width/2, height/2, 20, RED);
            }
            else
            {
                for (size_t i = 1; i < positions.size(); ++i)
                {
                    DrawLine(positions[i-1].x, positions[i-1].y, positions[i].x, positions[i].y, GOLD);
                }

                if (finished)
                {
                    std::string msg = "Accuracy: " + std::to_string(accuracy) + "%";
                    DrawText(msg.c_str(), width/2, height * 0.25, 20, GREEN);
                }
            }

            EndDrawing();

        }
    }

private:
    const int width = 800;
    const int height = 800;

    std::vector<Vector2> positions;
    bool finished = true;
    double accuracy = 0.0;
    std::string error = "";
};

int main(void)
{
    DrawALine instance{};
    instance.main();
    CloseWindow();
}