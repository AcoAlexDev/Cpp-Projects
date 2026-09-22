#include <iostream>
#include <raylib.h>

#include "algorithms.cpp"

static constexpr int WIDTH {1000};
static constexpr int HEIGHT {1000};
static constexpr int BORDER {10};

int main()
{
    InitWindow(WIDTH, HEIGHT, "SortingVisualizer");
    SetTargetFPS(120);
    InsertionSort instance{0 + BORDER, 0 + BORDER, 500 - BORDER * 2, 500 - BORDER * 2};
    SelectionSort instance2{500 + BORDER, 0 + BORDER, 500 - BORDER * 2, 500 - BORDER * 2};
    BubbleSort instance3{0 + BORDER, 500 + BORDER, 500 - BORDER * 2, 500 - BORDER * 2};
    GnomeSort instance4{500 + BORDER, 500 + BORDER, 500 - BORDER * 2, 500 - BORDER * 2};
    while(!WindowShouldClose())
    {
        PollInputEvents();
        BeginDrawing();
        instance.main();
        instance2.main();
        instance3.main();
        instance4.main();
        EndDrawing();

        ClearBackground(BLACK);
    }
}