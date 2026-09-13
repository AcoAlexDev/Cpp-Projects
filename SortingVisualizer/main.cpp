#include <iostream>
#include <raylib.h>

#include "algorithms.cpp"

static constexpr int WIDTH {1000};
static constexpr int HEIGHT {1000};

int main()
{
    InitWindow(WIDTH, HEIGHT, "SortingVisualizer");
    SetTargetFPS(60);
    InsertionSort instance{0, 0, 500, 500};
    SelectionSort instance2{500, 0, 500, 500};
    BubbleSort instance3{0, 500, 500, 500};
    GnomeSort instance4{500, 500, 500, 500};
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