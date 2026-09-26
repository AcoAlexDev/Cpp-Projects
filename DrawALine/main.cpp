#include <iostream>
#include <array>
#include <vector>
#include <string>
#include <raylib.h>

class DrawALine
{
public:
    double calculateAccuracy()
    {
        finished = true;
        int smallestX = -1;
        int highestX = -1;

        int smallestY = -1;
        int highestY = -1;

        for (size_t i = 0; i < positions.size(); ++i)
        {
            if(positions[i].x < smallestX || smallestX == -1)
            {
                smallestX = positions[i].x;
            }
            if(positions[i].x > highestX)
            {
                highestX = positions[i].x;
            }

            if(positions[i].y < smallestY || smallestY == -1)
            {
                smallestY = positions[i].y;
            }
            if(positions[i].y > highestY)
            {
                highestY = positions[i].y;
            }
        }

        if(smallestX == -1 || highestX == -1 || smallestY == -1 || highestY == -1)
        {
            error = "Invalid shape";
            return -100.0;
        }
        if(highestX - smallestX < 400)
        {
            error = "Line is too short";
            return 0.0;
        }

        double offset = 0.0;
        int yMid = (smallestY + highestY) * 0.5;
        for (size_t i = 0; i < positions.size(); ++i)
        {
            offset += std::abs(positions[i].y - yMid);
        }

        double avgOffset = offset / static_cast<double>(positions.size());
        double maxAcceptableOffset = 30.0; // pixels — tune to taste; smaller = stricter
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