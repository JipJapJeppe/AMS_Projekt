#include "Display.hpp"

#define old_max_val 480
#define old_min_val -480
#define new_max_val 100
#define new_min_val 0

#define clear() printf("\033[H\033[J")

void Display::init()
{
    for (int i = 0; i < 300; i++)
    {
        printf("\n");
    }
}

void Display::plot_point(int16_t *new_data)
{
    point dot = generatePoint(new_data);
    // printf("x: %i, y: %i\n", dot.x, dot.y);

    // std::cout << '\b';
    // std::cout << " ";
    moveCursor(dot.x, dot.y);
    std::cout << "#";
}

point Display::generatePoint(int16_t *new_data)
{
    int old_range = (old_max_val - old_min_val);
    int new_range = (new_max_val - new_min_val);

    point data = {};

    data.x = (((new_data[0] - old_min_val) * new_range) / old_range) + new_min_val;
    data.y = (((new_data[1] - old_min_val) * new_range) / old_range) + new_min_val;

    return data;
}

void Display::moveCursor(int col, int row)
{
    std::cout << "\033[" << col << ";" << row << "H";
}
