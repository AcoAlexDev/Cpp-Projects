#include <iostream>
#include <raylib.h>
#include <random>
#include <vector>

[[nodiscard]] inline std::vector<float> createRandomVector(size_t size)
{
    std::vector<float> v;
    std::mt19937 rng {};
    std::uniform_real_distribution<float> range {0.0f, 1.0f};
    for (size_t i {}; i < size; i++)
    {
        v.push_back(range(rng));
    }
    return v;
}

class SortingVisualizerPrefab {
    public:
        SortingVisualizerPrefab(int positionX, int positionY, int w, int h) :
        posX(positionX), posY(positionY), width(w), height(h)
        {
            v = createRandomVector(MAX_AMOUNT);
        }

        void main() {
            draw_array();
            sort_step();
        }

        void draw_array()
        {
            float x_step {width / static_cast<float>(MAX_AMOUNT)};
            for (size_t i {}; i < MAX_AMOUNT; i++){
                float height_rect {v[i] * height};
                DrawRectangle(posX + x_step * i, posY + height - height_rect, x_step, height_rect, WHITE);
            }
        }

        virtual void sort_step() = 0;

    protected:
        std::vector<float> v {};
        static constexpr size_t MAX_AMOUNT {100};

        int posX, posY, width, height;

};

class InsertionSort : public SortingVisualizerPrefab
{
public:
    InsertionSort(int pX, int pY, int w, int h) : SortingVisualizerPrefab(pX, pY, w, h) {}
private:
    void sort_step() override
    {   
        key = -1;
        for (size_t i = 1; i < MAX_AMOUNT; ++i)
        {
            if (v[i] < v[i - 1])
            {
                key = v[i];
                kid = i;
                break;
            }
        }

        if (key == -1) return;

        for( size_t i = 0; i < MAX_AMOUNT; ++i)
        {
            if (key < v[i])
            {
                v[kid] = v[i];
                v[i] = key;
                break;
            }
        }


    }
    float key{0};
    size_t kid{0};
};

class SelectionSort : public SortingVisualizerPrefab
{
public:
    SelectionSort(int pX, int pY, int w, int h) : SortingVisualizerPrefab(pX, pY, w, h) {}
private:
    void sort_step() override
    {   
        if (right >= MAX_AMOUNT - 1) return;

        if (v[i] < smallestVal)
        {
            smallestVal = v[i];
            smallestId = i;
        }
        i++;
        if (i == MAX_AMOUNT)
        {
            v[smallestId] = v[right];
            v[right] = smallestVal;
            right++;
            i = right;
            smallestVal = v[right];
            smallestId = right;
        }

        // for (size_t i = right; i < MAX_AMOUNT; ++i)
        // {
        //     if (v[i] < smallestVal)
        //     {
        //         smallestVal = v[i];
        //         smallestId = i;
        //     }
        // }
        // v[smallestId] = v[right];
        // v[right] = smallestVal;
        // right++;
    }
    size_t right {0};
    size_t i {0};
    float smallestVal = v[right];
    size_t smallestId = right;
};

class BubbleSort : public SortingVisualizerPrefab
{
public:
    BubbleSort(int pX, int pY, int w, int h) : SortingVisualizerPrefab(pX, pY, w, h) {}
private:
    void sort_step() override
    {   
        if (right == 0) return;

        if (v[i + 1] < v[i])
        {
            float s = v[i+1];
            v[i+1] = v[i];
            v[i] = s;
        }
        i++;
        if (i == right)
        {
            i = 0;
            right--;
        }

        // for (int i = 0; i < right; ++i)
        // {
        //     if (v[i + 1] < v[i])
        //     {
        //         float s = v[i+1];
        //         v[i+1] = v[i];
        //         v[i] = s;
        //     }
        // }
        // right--;
    }
    int right {MAX_AMOUNT - 1};
    int i {0};
};

class GnomeSort : public SortingVisualizerPrefab
{
public:
    GnomeSort(int pX, int pY, int w, int h) : SortingVisualizerPrefab(pX, pY, w, h) {}
private:
    void sort_step() override
    {   
        if (right >= static_cast<int>(MAX_AMOUNT) -1) return;

        if (v[right + 1] < v[right])
        {
            float saved = v[right];
            v[right] = v[right + 1];
            v[right + 1] = saved;
            right--;
            if (right < 0) right = 0;
        }
        else
        {
            right++;
        }
    }
    int right {0};
};